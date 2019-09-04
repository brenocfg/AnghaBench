#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* putC ) (TYPE_1__*,unsigned char) ;} ;
typedef  TYPE_1__ gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  IO_DBG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gd_error (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,unsigned char) ; 

void gdPutInt (int w, gdIOCtx * ctx)
{
	IO_DBG (gd_error("Putting int..."));
	(ctx->putC) (ctx, (unsigned char) (w >> 24));
	(ctx->putC) (ctx, (unsigned char) ((w >> 16) & 0xFF));
	(ctx->putC) (ctx, (unsigned char) ((w >> 8) & 0xFF));
	(ctx->putC) (ctx, (unsigned char) (w & 0xFF));
	IO_DBG (gd_error("put."));
}