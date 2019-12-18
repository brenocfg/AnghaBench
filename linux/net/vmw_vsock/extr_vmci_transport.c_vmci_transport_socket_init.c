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
struct vsock_sock {int /*<<< orphan*/  sk; int /*<<< orphan*/  trans; } ;
struct vmci_transport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_pair_max_size; int /*<<< orphan*/  queue_pair_min_size; int /*<<< orphan*/  queue_pair_size; int /*<<< orphan*/  lock; int /*<<< orphan*/ * sk; int /*<<< orphan*/  elem; int /*<<< orphan*/ * notify_ops; int /*<<< orphan*/  detach_sub_id; scalar_t__ consume_size; scalar_t__ produce_size; int /*<<< orphan*/ * qpair; void* qp_handle; void* dg_handle; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* VMCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  VMCI_INVALID_ID ; 
 int /*<<< orphan*/  VMCI_TRANSPORT_DEFAULT_QP_SIZE ; 
 int /*<<< orphan*/  VMCI_TRANSPORT_DEFAULT_QP_SIZE_MAX ; 
 int /*<<< orphan*/  VMCI_TRANSPORT_DEFAULT_QP_SIZE_MIN ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* vmci_trans (struct vsock_sock*) ; 

__attribute__((used)) static int vmci_transport_socket_init(struct vsock_sock *vsk,
				      struct vsock_sock *psk)
{
	vsk->trans = kmalloc(sizeof(struct vmci_transport), GFP_KERNEL);
	if (!vsk->trans)
		return -ENOMEM;

	vmci_trans(vsk)->dg_handle = VMCI_INVALID_HANDLE;
	vmci_trans(vsk)->qp_handle = VMCI_INVALID_HANDLE;
	vmci_trans(vsk)->qpair = NULL;
	vmci_trans(vsk)->produce_size = vmci_trans(vsk)->consume_size = 0;
	vmci_trans(vsk)->detach_sub_id = VMCI_INVALID_ID;
	vmci_trans(vsk)->notify_ops = NULL;
	INIT_LIST_HEAD(&vmci_trans(vsk)->elem);
	vmci_trans(vsk)->sk = &vsk->sk;
	spin_lock_init(&vmci_trans(vsk)->lock);
	if (psk) {
		vmci_trans(vsk)->queue_pair_size =
			vmci_trans(psk)->queue_pair_size;
		vmci_trans(vsk)->queue_pair_min_size =
			vmci_trans(psk)->queue_pair_min_size;
		vmci_trans(vsk)->queue_pair_max_size =
			vmci_trans(psk)->queue_pair_max_size;
	} else {
		vmci_trans(vsk)->queue_pair_size =
			VMCI_TRANSPORT_DEFAULT_QP_SIZE;
		vmci_trans(vsk)->queue_pair_min_size =
			 VMCI_TRANSPORT_DEFAULT_QP_SIZE_MIN;
		vmci_trans(vsk)->queue_pair_max_size =
			VMCI_TRANSPORT_DEFAULT_QP_SIZE_MAX;
	}

	return 0;
}