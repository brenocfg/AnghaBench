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
typedef  int u8 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int len; } ;
struct TYPE_4__ {int /*<<< orphan*/  complete; } ;
struct at86rf230_state_change {int* buf; TYPE_1__ trx; TYPE_2__ msg; struct at86rf230_local* lp; } ;
struct at86rf230_local {int is_tx; int /*<<< orphan*/  spi; struct sk_buff* tx_skb; } ;

/* Variables and functions */
 int CMD_FB ; 
 int CMD_WRITE ; 
 int /*<<< orphan*/  at86rf230_async_error (struct at86rf230_local*,struct at86rf230_state_change*,int) ; 
 int /*<<< orphan*/  at86rf230_write_frame_complete ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int spi_async (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
at86rf230_write_frame(void *context)
{
	struct at86rf230_state_change *ctx = context;
	struct at86rf230_local *lp = ctx->lp;
	struct sk_buff *skb = lp->tx_skb;
	u8 *buf = ctx->buf;
	int rc;

	lp->is_tx = 1;

	buf[0] = CMD_FB | CMD_WRITE;
	buf[1] = skb->len + 2;
	memcpy(buf + 2, skb->data, skb->len);
	ctx->trx.len = skb->len + 2;
	ctx->msg.complete = at86rf230_write_frame_complete;
	rc = spi_async(lp->spi, &ctx->msg);
	if (rc) {
		ctx->trx.len = 2;
		at86rf230_async_error(lp, ctx, rc);
	}
}