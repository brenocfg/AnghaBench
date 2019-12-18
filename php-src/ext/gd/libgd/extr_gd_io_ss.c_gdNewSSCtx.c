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
typedef  TYPE_2__* ssIOCtxPtr ;
typedef  int /*<<< orphan*/  ssIOCtx ;
typedef  int /*<<< orphan*/  gdSourcePtr ;
typedef  int /*<<< orphan*/  gdSinkPtr ;
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_3__ {int /*<<< orphan*/  gd_free; int /*<<< orphan*/ * seek; int /*<<< orphan*/ * tell; int /*<<< orphan*/  putBuf; int /*<<< orphan*/  putC; int /*<<< orphan*/  getBuf; int /*<<< orphan*/  getC; } ;
struct TYPE_4__ {TYPE_1__ ctx; int /*<<< orphan*/  snk; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdFreeSsCtx ; 
 scalar_t__ gdMalloc (int) ; 
 int /*<<< orphan*/  sinkPutbuf ; 
 int /*<<< orphan*/  sinkPutchar ; 
 int /*<<< orphan*/  sourceGetbuf ; 
 int /*<<< orphan*/  sourceGetchar ; 

gdIOCtx * gdNewSSCtx (gdSourcePtr src, gdSinkPtr snk)
{
	ssIOCtxPtr ctx;

	ctx = (ssIOCtxPtr) gdMalloc (sizeof (ssIOCtx));

	ctx->src = src;
	ctx->snk = snk;

	ctx->ctx.getC = sourceGetchar;
	ctx->ctx.getBuf = sourceGetbuf;

	ctx->ctx.putC = sinkPutchar;
	ctx->ctx.putBuf = sinkPutbuf;

	ctx->ctx.tell = NULL;
	ctx->ctx.seek = NULL;

	ctx->ctx.gd_free = gdFreeSsCtx;

	return (gdIOCtx *) ctx;
}