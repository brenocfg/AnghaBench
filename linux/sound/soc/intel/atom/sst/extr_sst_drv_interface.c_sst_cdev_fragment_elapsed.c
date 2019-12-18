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
struct stream_info {int /*<<< orphan*/  compr_cb_param; int /*<<< orphan*/  (* compr_cb ) (int /*<<< orphan*/ ) ;} ;
struct intel_sst_drv {struct stream_info* streams; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void sst_cdev_fragment_elapsed(struct intel_sst_drv *ctx, int str_id)
{
	struct stream_info *stream;

	dev_dbg(ctx->dev, "fragment elapsed from firmware for str_id %d\n",
			str_id);
	stream = &ctx->streams[str_id];
	if (stream->compr_cb)
		stream->compr_cb(stream->compr_cb_param);
}