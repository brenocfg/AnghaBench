#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct trf7970a {int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trf7970a_send_upstream (struct trf7970a*) ; 

__attribute__((used)) static void trf7970a_send_err_upstream(struct trf7970a *trf, int errno)
{
	dev_dbg(trf->dev, "Error - state: %d, errno: %d\n", trf->state, errno);

	cancel_delayed_work(&trf->timeout_work);

	kfree_skb(trf->rx_skb);
	trf->rx_skb = ERR_PTR(errno);

	trf7970a_send_upstream(trf);
}