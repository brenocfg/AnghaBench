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
struct trf7970a {int aborting; TYPE_1__* rx_skb; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  ddev; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ;int /*<<< orphan*/  dev; int /*<<< orphan*/  state; int /*<<< orphan*/ * tx_skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  ECANCELED ; 
 TYPE_1__* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  TRF7970A_ST_IDLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (TYPE_1__*) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void trf7970a_send_upstream(struct trf7970a *trf)
{
	dev_kfree_skb_any(trf->tx_skb);
	trf->tx_skb = NULL;

	if (trf->rx_skb && !IS_ERR(trf->rx_skb) && !trf->aborting)
		print_hex_dump_debug("trf7970a rx data: ", DUMP_PREFIX_NONE,
				     16, 1, trf->rx_skb->data, trf->rx_skb->len,
				     false);

	trf->state = TRF7970A_ST_IDLE;

	if (trf->aborting) {
		dev_dbg(trf->dev, "Abort process complete\n");

		if (!IS_ERR(trf->rx_skb)) {
			kfree_skb(trf->rx_skb);
			trf->rx_skb = ERR_PTR(-ECANCELED);
		}

		trf->aborting = false;
	}

	trf->cb(trf->ddev, trf->cb_arg, trf->rx_skb);

	trf->rx_skb = NULL;
}