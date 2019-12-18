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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct vmci_transport_waiting_info {int dummy; } ;
struct vmci_transport_packet {int dummy; } ;
struct vmci_handle {int dummy; } ;
struct sockaddr_vm {int dummy; } ;
typedef  enum vmci_transport_packet_type { ____Placeholder_vmci_transport_packet_type } vmci_transport_packet_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __vmci_transport_send_control_pkt (struct vmci_transport_packet*,struct sockaddr_vm*,struct sockaddr_vm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmci_transport_waiting_info*,int /*<<< orphan*/ ,struct vmci_handle,int) ; 
 int /*<<< orphan*/  kfree (struct vmci_transport_packet*) ; 
 struct vmci_transport_packet* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmci_transport_alloc_send_control_pkt(struct sockaddr_vm *src,
				      struct sockaddr_vm *dst,
				      enum vmci_transport_packet_type type,
				      u64 size,
				      u64 mode,
				      struct vmci_transport_waiting_info *wait,
				      u16 proto,
				      struct vmci_handle handle)
{
	struct vmci_transport_packet *pkt;
	int err;

	pkt = kmalloc(sizeof(*pkt), GFP_KERNEL);
	if (!pkt)
		return -ENOMEM;

	err = __vmci_transport_send_control_pkt(pkt, src, dst, type, size,
						mode, wait, proto, handle,
						true);
	kfree(pkt);

	return err;
}