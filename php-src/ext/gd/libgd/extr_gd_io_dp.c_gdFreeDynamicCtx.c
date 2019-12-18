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
struct gdIOCtx {scalar_t__ logicalSize; scalar_t__ realSize; } ;
typedef  struct gdIOCtx dynamicPtr ;
struct TYPE_2__ {struct gdIOCtx* dp; } ;
typedef  TYPE_1__ dpIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  gdFree (struct gdIOCtx*) ; 

__attribute__((used)) static void gdFreeDynamicCtx (struct gdIOCtx *ctx)
{
	dynamicPtr *dp;
	dpIOCtx *dctx;

	dctx = (dpIOCtx *) ctx;
	dp = dctx->dp;

	gdFree(ctx);

	dp->realSize = 0;
	dp->logicalSize = 0;

	gdFree(dp);
}