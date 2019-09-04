#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct nfc_llcp_local {int lto; int local_wks; int /*<<< orphan*/  list; int /*<<< orphan*/  sdreq_timeout_work; int /*<<< orphan*/  sdreq_timer; int /*<<< orphan*/  pending_sdreqs; int /*<<< orphan*/  sdreq_lock; int /*<<< orphan*/  remote_lto; int /*<<< orphan*/  remote_miu; int /*<<< orphan*/  miux; int /*<<< orphan*/  rw; TYPE_3__ raw_sockets; TYPE_2__ connecting_sockets; TYPE_1__ sockets; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  rx_work; int /*<<< orphan*/ * rx_pending; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  link_timer; int /*<<< orphan*/  sdp_lock; int /*<<< orphan*/  ref; struct nfc_dev* dev; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLCP_DEFAULT_LTO ; 
 int /*<<< orphan*/  LLCP_DEFAULT_MIU ; 
 int /*<<< orphan*/  LLCP_MAX_MIUX ; 
 int /*<<< orphan*/  LLCP_MAX_RW ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nfc_llcp_local* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llcp_devices ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_llcp_build_gb (struct nfc_llcp_local*) ; 
 int /*<<< orphan*/  nfc_llcp_rx_work ; 
 int /*<<< orphan*/  nfc_llcp_sdreq_timeout_work ; 
 int /*<<< orphan*/  nfc_llcp_sdreq_timer ; 
 int /*<<< orphan*/  nfc_llcp_symm_timer ; 
 int /*<<< orphan*/  nfc_llcp_timeout_work ; 
 int /*<<< orphan*/  nfc_llcp_tx_work ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfc_llcp_register_device(struct nfc_dev *ndev)
{
	struct nfc_llcp_local *local;

	local = kzalloc(sizeof(struct nfc_llcp_local), GFP_KERNEL);
	if (local == NULL)
		return -ENOMEM;

	local->dev = ndev;
	INIT_LIST_HEAD(&local->list);
	kref_init(&local->ref);
	mutex_init(&local->sdp_lock);
	timer_setup(&local->link_timer, nfc_llcp_symm_timer, 0);

	skb_queue_head_init(&local->tx_queue);
	INIT_WORK(&local->tx_work, nfc_llcp_tx_work);

	local->rx_pending = NULL;
	INIT_WORK(&local->rx_work, nfc_llcp_rx_work);

	INIT_WORK(&local->timeout_work, nfc_llcp_timeout_work);

	rwlock_init(&local->sockets.lock);
	rwlock_init(&local->connecting_sockets.lock);
	rwlock_init(&local->raw_sockets.lock);

	local->lto = 150; /* 1500 ms */
	local->rw = LLCP_MAX_RW;
	local->miux = cpu_to_be16(LLCP_MAX_MIUX);
	local->local_wks = 0x1; /* LLC Link Management */

	nfc_llcp_build_gb(local);

	local->remote_miu = LLCP_DEFAULT_MIU;
	local->remote_lto = LLCP_DEFAULT_LTO;

	mutex_init(&local->sdreq_lock);
	INIT_HLIST_HEAD(&local->pending_sdreqs);
	timer_setup(&local->sdreq_timer, nfc_llcp_sdreq_timer, 0);
	INIT_WORK(&local->sdreq_timeout_work, nfc_llcp_sdreq_timeout_work);

	list_add(&local->list, &llcp_devices);

	return 0;
}