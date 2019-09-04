#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* getC ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  GD_IO_EOF_CHK (int) ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 

int gdGetWord (int *result, gdIOCtx * ctx)
{
	int r;
	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result = r << 8;
	r = (ctx->getC) (ctx);
	GD_IO_EOF_CHK(r);
	*result += r;
	return 1;
}