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
struct ra_ctx {struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_bos; int /*<<< orphan*/ * bo_queue; } ;
struct priv {TYPE_1__ gbm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dequeue_bo(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;

    talloc_free(p->gbm.bo_queue[0]);
    MP_TARRAY_REMOVE_AT(p->gbm.bo_queue, p->gbm.num_bos, 0);
}