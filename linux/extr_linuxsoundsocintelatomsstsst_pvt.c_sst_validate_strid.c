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
struct TYPE_2__ {int max_streams; } ;
struct intel_sst_drv {TYPE_1__ info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 

int sst_validate_strid(
		struct intel_sst_drv *sst_drv_ctx, int str_id)
{
	if (str_id <= 0 || str_id > sst_drv_ctx->info.max_streams) {
		dev_err(sst_drv_ctx->dev,
			"SST ERR: invalid stream id : %d, max %d\n",
			str_id, sst_drv_ctx->info.max_streams);
		return -EINVAL;
	}

	return 0;
}