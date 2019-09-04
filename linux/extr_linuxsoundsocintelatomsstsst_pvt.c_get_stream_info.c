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
struct intel_sst_drv {struct stream_info* streams; } ;

/* Variables and functions */
 scalar_t__ sst_validate_strid (struct intel_sst_drv*,int) ; 

struct stream_info *get_stream_info(
		struct intel_sst_drv *sst_drv_ctx, int str_id)
{
	if (sst_validate_strid(sst_drv_ctx, str_id))
		return NULL;
	return &sst_drv_ctx->streams[str_id];
}