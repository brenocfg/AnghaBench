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
struct snd_pcm_substream {int dummy; } ;
struct lola_stream {int period_bytes; int bufsize; int index; scalar_t__ frags; } ;
struct TYPE_3__ {scalar_t__ area; } ;
struct lola_pcm {TYPE_1__ bdl; } ;
struct lola {TYPE_2__* card; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int LOLA_BDL_ENTRY_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int setup_bdle (struct snd_pcm_substream*,struct lola_stream*,int /*<<< orphan*/ **,int,int) ; 

__attribute__((used)) static int lola_setup_periods(struct lola *chip, struct lola_pcm *pcm,
			      struct snd_pcm_substream *substream,
			      struct lola_stream *str)
{
	__le32 *bdl;
	int i, ofs, periods, period_bytes;

	period_bytes = str->period_bytes;
	periods = str->bufsize / period_bytes;

	/* program the initial BDL entries */
	bdl = (__le32 *)(pcm->bdl.area + LOLA_BDL_ENTRY_SIZE * str->index);
	ofs = 0;
	str->frags = 0;
	for (i = 0; i < periods; i++) {
		ofs = setup_bdle(substream, str, &bdl, ofs, period_bytes);
		if (ofs < 0)
			goto error;
	}
	return 0;

 error:
	dev_err(chip->card->dev, "Too many BDL entries: buffer=%d, period=%d\n",
		   str->bufsize, period_bytes);
	return -EINVAL;
}