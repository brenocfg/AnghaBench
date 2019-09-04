#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ssIOCtxPtr ;
struct TYPE_5__ {TYPE_1__* snk; } ;
typedef  TYPE_2__ ssIOCtx ;
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_4__ {int (* sink ) (int /*<<< orphan*/ ,void const*,int) ;int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int sinkPutbuf (gdIOCtx * ctx, const void *buf, int size)
{
	ssIOCtxPtr lctx;
	int res;

	lctx = (ssIOCtx *) ctx;

	res = (lctx->snk->sink) (lctx->snk->context, buf, size);

	if (res <= 0) {
		return 0;
	} else {
		return res;
	}
}