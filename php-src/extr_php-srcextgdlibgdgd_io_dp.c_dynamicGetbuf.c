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
typedef  scalar_t__ gdIOCtxPtr ;
struct TYPE_3__ {int logicalSize; int pos; scalar_t__ data; } ;
typedef  TYPE_1__ dynamicPtr ;
typedef  TYPE_2__* dpIOCtxPtr ;
struct TYPE_4__ {TYPE_1__* dp; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static int dynamicGetbuf (gdIOCtxPtr ctx, void *buf, int len)
{
	int rlen, remain;
	dpIOCtxPtr dctx;
	dynamicPtr *dp;

	dctx = (dpIOCtxPtr) ctx;
	dp = dctx->dp;

	remain = dp->logicalSize - dp->pos;
	if (remain >= len) {
		rlen = len;
	} else {
		if (remain <= 0) {
			return EOF;
		}
		rlen = remain;
	}

	memcpy(buf, (void *) ((char *) dp->data + dp->pos), rlen);
	dp->pos += rlen;

	return rlen;
}