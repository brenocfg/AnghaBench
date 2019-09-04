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
struct sdw_link_data {scalar_t__ pdev; } ;
struct sdw_intel_ctx {int count; struct sdw_link_data* links; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sdw_link_data*) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 

__attribute__((used)) static int sdw_intel_cleanup_pdev(struct sdw_intel_ctx *ctx)
{
	struct sdw_link_data *link = ctx->links;
	int i;

	if (!link)
		return 0;

	for (i = 0; i < ctx->count; i++) {
		if (link->pdev)
			platform_device_unregister(link->pdev);
		link++;
	}

	kfree(ctx->links);
	ctx->links = NULL;

	return 0;
}