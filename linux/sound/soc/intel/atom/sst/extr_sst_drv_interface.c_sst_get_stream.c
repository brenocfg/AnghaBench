#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stream_info {int /*<<< orphan*/  sfreq; } ;
struct snd_sst_params {int dummy; } ;
struct intel_sst_drv {struct stream_info* streams; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* alloc_stream ) (struct intel_sst_drv*,struct snd_sst_params*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  sst_get_sfreq (struct snd_sst_params*) ; 
 int stub1 (struct intel_sst_drv*,struct snd_sst_params*) ; 

int sst_get_stream(struct intel_sst_drv *ctx,
			struct snd_sst_params *str_param)
{
	int retval;
	struct stream_info *str_info;

	/* stream is not allocated, we are allocating */
	retval = ctx->ops->alloc_stream(ctx, str_param);
	if (retval <= 0) {
		return -EIO;
	}
	/* store sampling freq */
	str_info = &ctx->streams[retval];
	str_info->sfreq = sst_get_sfreq(str_param);

	return retval;
}