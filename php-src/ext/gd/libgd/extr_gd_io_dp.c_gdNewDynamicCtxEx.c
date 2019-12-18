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
typedef  int /*<<< orphan*/  gdIOCtx ;
typedef  int /*<<< orphan*/  dynamicPtr ;
struct TYPE_3__ {int /*<<< orphan*/  gd_free; int /*<<< orphan*/  tell; int /*<<< orphan*/  seek; int /*<<< orphan*/  putBuf; int /*<<< orphan*/  getBuf; int /*<<< orphan*/  putC; int /*<<< orphan*/  getC; } ;
struct TYPE_4__ {TYPE_1__ ctx; int /*<<< orphan*/ * dp; } ;
typedef  TYPE_2__ dpIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  dynamicGetbuf ; 
 int /*<<< orphan*/  dynamicGetchar ; 
 int /*<<< orphan*/  dynamicPutbuf ; 
 int /*<<< orphan*/  dynamicPutchar ; 
 int /*<<< orphan*/  dynamicSeek ; 
 int /*<<< orphan*/  dynamicTell ; 
 int /*<<< orphan*/  gdFreeDynamicCtx ; 
 scalar_t__ gdMalloc (int) ; 
 int /*<<< orphan*/ * newDynamic (int,void*,int) ; 

gdIOCtx * gdNewDynamicCtxEx (int initialSize, void *data, int freeOKFlag)
{
	dpIOCtx *ctx;
	dynamicPtr *dp;

	ctx = (dpIOCtx *) gdMalloc (sizeof (dpIOCtx));

	dp = newDynamic(initialSize, data, freeOKFlag);

	ctx->dp = dp;

	ctx->ctx.getC = dynamicGetchar;
	ctx->ctx.putC = dynamicPutchar;

	ctx->ctx.getBuf = dynamicGetbuf;
	ctx->ctx.putBuf = dynamicPutbuf;

	ctx->ctx.seek = dynamicSeek;
	ctx->ctx.tell = dynamicTell;

	ctx->ctx.gd_free = gdFreeDynamicCtx;

	return (gdIOCtx *) ctx;
}