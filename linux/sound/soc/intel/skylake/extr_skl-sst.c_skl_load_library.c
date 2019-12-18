#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sst_dsp {struct skl_dev* thread_context; } ;
struct skl_lib_info {int dummy; } ;
struct skl_dev {int /*<<< orphan*/ * lib_info; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_ADSP_FW_BIN_HDR_OFFSET ; 
 int skl_prepare_lib_load (struct skl_dev*,int /*<<< orphan*/ *,struct firmware*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skl_release_library (struct skl_lib_info*,int) ; 
 int skl_transfer_module (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
skl_load_library(struct sst_dsp *ctx, struct skl_lib_info *linfo, int lib_count)
{
	struct skl_dev *skl = ctx->thread_context;
	struct firmware stripped_fw;
	int ret, i;

	/* library indices start from 1 to N. 0 represents base FW */
	for (i = 1; i < lib_count; i++) {
		ret = skl_prepare_lib_load(skl, &skl->lib_info[i], &stripped_fw,
					SKL_ADSP_FW_BIN_HDR_OFFSET, i);
		if (ret < 0)
			goto load_library_failed;
		ret = skl_transfer_module(ctx, stripped_fw.data,
				stripped_fw.size, 0, i, false);
		if (ret < 0)
			goto load_library_failed;
	}

	return 0;

load_library_failed:
	skl_release_library(linfo, lib_count);
	return ret;
}