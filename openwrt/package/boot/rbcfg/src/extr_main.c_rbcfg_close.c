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
struct rbcfg_ctx {struct rbcfg_ctx* mtd_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct rbcfg_ctx*) ; 
 struct rbcfg_ctx* rbcfg_ctx ; 

__attribute__((used)) static void
rbcfg_close(void)
{
	struct rbcfg_ctx *ctx;

	ctx = rbcfg_ctx;
	free(ctx->mtd_device);
	free(ctx);
}