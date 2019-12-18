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
struct snd_sst_params {int dummy; } ;
struct snd_sst_lib_download {int dummy; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* alloc_stream ) (struct intel_sst_drv*,struct snd_sst_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct intel_sst_drv*,struct snd_sst_params*) ; 

int sst_get_stream_allocated(struct intel_sst_drv *ctx,
	struct snd_sst_params *str_param,
	struct snd_sst_lib_download **lib_dnld)
{
	int retval;

	retval = ctx->ops->alloc_stream(ctx, str_param);
	if (retval > 0)
		dev_dbg(ctx->dev, "Stream allocated %d\n", retval);
	return retval;

}