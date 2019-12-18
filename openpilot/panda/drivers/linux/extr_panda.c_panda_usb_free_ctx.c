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
struct panda_usb_ctx {TYPE_1__* priv; int /*<<< orphan*/  ndx; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; int /*<<< orphan*/  free_ctx_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANDA_CTX_FREE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void panda_usb_free_ctx(struct panda_usb_ctx *ctx)
{
  /* Increase number of free ctxs before freeing ctx */
  atomic_inc(&ctx->priv->free_ctx_cnt);

  ctx->ndx = PANDA_CTX_FREE;

  /* Wake up the queue once ctx is marked free */
  netif_wake_queue(ctx->priv->netdev);
}