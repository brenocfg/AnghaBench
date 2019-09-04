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
struct nfc_llcp_local {int /*<<< orphan*/  pending_sdreqs; int /*<<< orphan*/  sdreq_timeout_work; int /*<<< orphan*/  sdreq_timer; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  link_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_llcp_free_sdp_tlv_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_llcp_socket_release (struct nfc_llcp_local*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void local_cleanup(struct nfc_llcp_local *local)
{
	nfc_llcp_socket_release(local, false, ENXIO);
	del_timer_sync(&local->link_timer);
	skb_queue_purge(&local->tx_queue);
	cancel_work_sync(&local->tx_work);
	cancel_work_sync(&local->rx_work);
	cancel_work_sync(&local->timeout_work);
	kfree_skb(local->rx_pending);
	del_timer_sync(&local->sdreq_timer);
	cancel_work_sync(&local->sdreq_timeout_work);
	nfc_llcp_free_sdp_tlv_list(&local->pending_sdreqs);
}