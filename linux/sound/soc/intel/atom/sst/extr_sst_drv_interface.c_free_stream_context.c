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
struct stream_info {int dummy; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; int /*<<< orphan*/ * streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct stream_info* get_stream_info (struct intel_sst_drv*,unsigned int) ; 
 int /*<<< orphan*/  sst_clean_stream (int /*<<< orphan*/ *) ; 
 int sst_free_stream (struct intel_sst_drv*,unsigned int) ; 

int free_stream_context(struct intel_sst_drv *ctx, unsigned int str_id)
{
	struct stream_info *stream;
	int ret = 0;

	stream = get_stream_info(ctx, str_id);
	if (stream) {
		/* str_id is valid, so stream is alloacted */
		ret = sst_free_stream(ctx, str_id);
		if (ret)
			sst_clean_stream(&ctx->streams[str_id]);
		return ret;
	} else {
		dev_err(ctx->dev, "we tried to free stream context %d which was freed!!!\n", str_id);
	}
	return ret;
}