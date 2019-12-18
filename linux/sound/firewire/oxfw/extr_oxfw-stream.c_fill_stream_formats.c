#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct snd_oxfw_stream_formation {int dummy; } ;
struct snd_oxfw {TYPE_2__* unit; TYPE_1__* card; int /*<<< orphan*/ ** rx_stream_formats; int /*<<< orphan*/ ** tx_stream_formats; } ;
typedef  enum avc_general_plug_dir { ____Placeholder_avc_general_plug_dir } avc_general_plug_dir ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/  card_dev; } ;

/* Variables and functions */
 int AVC_GENERAL_PLUG_DIR_IN ; 
 int AVC_GENERAL_PLUG_DIR_OUT ; 
 unsigned int AVC_GENERIC_FRAME_MAXIMUM_BYTES ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SND_OXFW_STREAM_FORMAT_ENTRIES ; 
 int assume_stream_formats (struct snd_oxfw*,int,unsigned short,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ **) ; 
 int avc_stream_get_format_list (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,char*,unsigned short,int) ; 
 int /*<<< orphan*/ * devm_kmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int snd_oxfw_stream_parse_format (int /*<<< orphan*/ *,struct snd_oxfw_stream_formation*) ; 

__attribute__((used)) static int fill_stream_formats(struct snd_oxfw *oxfw,
			       enum avc_general_plug_dir dir,
			       unsigned short pid)
{
	u8 *buf, **formats;
	unsigned int len, eid = 0;
	struct snd_oxfw_stream_formation dummy;
	int err;

	buf = kmalloc(AVC_GENERIC_FRAME_MAXIMUM_BYTES, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	if (dir == AVC_GENERAL_PLUG_DIR_OUT)
		formats = oxfw->tx_stream_formats;
	else
		formats = oxfw->rx_stream_formats;

	/* get first entry */
	len = AVC_GENERIC_FRAME_MAXIMUM_BYTES;
	err = avc_stream_get_format_list(oxfw->unit, dir, 0, buf, &len, 0);
	if (err == -ENOSYS) {
		/* LIST subfunction is not implemented */
		len = AVC_GENERIC_FRAME_MAXIMUM_BYTES;
		err = assume_stream_formats(oxfw, dir, pid, buf, &len,
					    formats);
		goto end;
	} else if (err < 0) {
		dev_err(&oxfw->unit->device,
			"fail to get stream format %d for isoc %s plug %d:%d\n",
			eid, (dir == AVC_GENERAL_PLUG_DIR_IN) ? "in" : "out",
			pid, err);
		goto end;
	}

	/* LIST subfunction is implemented */
	while (eid < SND_OXFW_STREAM_FORMAT_ENTRIES) {
		/* The format is too short. */
		if (len < 3) {
			err = -EIO;
			break;
		}

		/* parse and set stream format */
		err = snd_oxfw_stream_parse_format(buf, &dummy);
		if (err < 0)
			break;

		formats[eid] = devm_kmemdup(&oxfw->card->card_dev, buf, len,
					    GFP_KERNEL);
		if (!formats[eid]) {
			err = -ENOMEM;
			break;
		}

		/* get next entry */
		len = AVC_GENERIC_FRAME_MAXIMUM_BYTES;
		err = avc_stream_get_format_list(oxfw->unit, dir, 0,
						 buf, &len, ++eid);
		/* No entries remained. */
		if (err == -EINVAL) {
			err = 0;
			break;
		} else if (err < 0) {
			dev_err(&oxfw->unit->device,
			"fail to get stream format %d for isoc %s plug %d:%d\n",
				eid, (dir == AVC_GENERAL_PLUG_DIR_IN) ? "in" :
									"out",
				pid, err);
			break;
		}
	}
end:
	kfree(buf);
	return err;
}