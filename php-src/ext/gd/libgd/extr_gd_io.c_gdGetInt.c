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
struct TYPE_7__ {unsigned int (* getC ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ gdIOCtx ;

/* Variables and functions */
 unsigned int EOF ; 
 int /*<<< orphan*/  GD_IO_EOF_CHK (unsigned int) ; 
 unsigned int stub1 (TYPE_1__*) ; 
 unsigned int stub2 (TYPE_1__*) ; 
 unsigned int stub3 (TYPE_1__*) ; 
 unsigned int stub4 (TYPE_1__*) ; 

int gdGetInt (int *result, gdIOCtx * ctx)
{
	unsigned int r;
	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result = r << 24;

	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result += r << 16;

	r = (ctx->getC) (ctx);
	if (r == EOF) {
		return 0;
	}
	*result += r << 8;

	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result += r;

	return 1;
}