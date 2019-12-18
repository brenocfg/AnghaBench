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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int max_streams; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; TYPE_2__* streams; TYPE_1__ info; } ;
struct TYPE_4__ {scalar_t__ pipe_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 

int get_stream_id_mrfld(struct intel_sst_drv *sst_drv_ctx,
		u32 pipe_id)
{
	int i;

	for (i = 1; i <= sst_drv_ctx->info.max_streams; i++)
		if (pipe_id == sst_drv_ctx->streams[i].pipe_id)
			return i;

	dev_dbg(sst_drv_ctx->dev, "no such pipe_id(%u)", pipe_id);
	return -1;
}