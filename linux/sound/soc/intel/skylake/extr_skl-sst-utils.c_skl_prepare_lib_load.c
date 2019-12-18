#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sst_dsp {int dummy; } ;
struct skl_lib_info {TYPE_1__* fw; int /*<<< orphan*/  name; } ;
struct skl_dev {scalar_t__ is_first_boot; int /*<<< orphan*/  dev; struct sst_dsp* dsp; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int request_firmware (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_dsp_strip_extended_manifest (struct firmware*) ; 
 int snd_skl_parse_uuids (struct sst_dsp*,TYPE_1__*,unsigned int,int) ; 

int skl_prepare_lib_load(struct skl_dev *skl, struct skl_lib_info *linfo,
		struct firmware *stripped_fw,
		unsigned int hdr_offset, int index)
{
	int ret;
	struct sst_dsp *dsp = skl->dsp;

	if (linfo->fw == NULL) {
		ret = request_firmware(&linfo->fw, linfo->name,
					skl->dev);
		if (ret < 0) {
			dev_err(skl->dev, "Request lib %s failed:%d\n",
				linfo->name, ret);
			return ret;
		}
	}

	if (skl->is_first_boot) {
		ret = snd_skl_parse_uuids(dsp, linfo->fw, hdr_offset, index);
		if (ret < 0)
			return ret;
	}

	stripped_fw->data = linfo->fw->data;
	stripped_fw->size = linfo->fw->size;
	skl_dsp_strip_extended_manifest(stripped_fw);

	return 0;
}