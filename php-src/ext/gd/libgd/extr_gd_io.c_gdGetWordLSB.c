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
 int EOF ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 

int gdGetWordLSB(signed short int *result, gdIOCtx *ctx)
{
	int high = 0, low = 0;
	low = (ctx->getC) (ctx);
	if (low == EOF) {
		return 0;
	}

	high = (ctx->getC) (ctx);
	if (high == EOF) {
		return 0;
	}

	if (result) {
		*result = (high << 8) | low;
	}

	return 1;
}