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
struct stream_info {int /*<<< orphan*/ * period_elapsed; int /*<<< orphan*/  status; int /*<<< orphan*/ * pcm_substream; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; int /*<<< orphan*/  stream_cnt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  STREAM_UN_INIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 int free_stream_context (struct intel_sst_drv*,unsigned int) ; 
 struct stream_info* get_stream_info (struct intel_sst_drv*,unsigned int) ; 

__attribute__((used)) static int sst_close_pcm_stream(struct device *dev, unsigned int str_id)
{
	struct stream_info *stream;
	int retval = 0;
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);

	stream = get_stream_info(ctx, str_id);
	if (!stream) {
		dev_err(ctx->dev, "stream info is NULL for str %d!!!\n", str_id);
		return -EINVAL;
	}

	retval = free_stream_context(ctx, str_id);
	stream->pcm_substream = NULL;
	stream->status = STREAM_UN_INIT;
	stream->period_elapsed = NULL;
	ctx->stream_cnt--;

	if (retval)
		dev_err(ctx->dev, "free stream returned err %d\n", retval);

	dev_dbg(ctx->dev, "Exit\n");
	return 0;
}