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
struct TYPE_4__ {TYPE_1__* src; } ;
typedef  TYPE_2__ ssIOCtx ;
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_3__ {int (* source ) (int /*<<< orphan*/ ,void*,int) ;int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EOF ; 
 int stub1 (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int sourceGetbuf (gdIOCtx * ctx, void *buf, int size)
{
	ssIOCtx *lctx;
	int res;

	lctx = (ssIOCtx *) ctx;

	res = ((lctx->src->source) (lctx->src->context, buf, size));

	/*
	 * Translate the return values from the Source object:
	 * 0 is EOF, -1 is error
	 */

	if (res == 0) {
		return EOF;
	} else if (res < 0) {
		return 0;
	} else {
		return res;
	}
}