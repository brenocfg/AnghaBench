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
struct nfc_llcp_sock {int /*<<< orphan*/  local; int /*<<< orphan*/ * parent; int /*<<< orphan*/  accept_queue; int /*<<< orphan*/  tx_pending_queue; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  service_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_llcp_local_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void nfc_llcp_sock_free(struct nfc_llcp_sock *sock)
{
	kfree(sock->service_name);

	skb_queue_purge(&sock->tx_queue);
	skb_queue_purge(&sock->tx_pending_queue);

	list_del_init(&sock->accept_queue);

	sock->parent = NULL;

	nfc_llcp_local_put(sock->local);
}