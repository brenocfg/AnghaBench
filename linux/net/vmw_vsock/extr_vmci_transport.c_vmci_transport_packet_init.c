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
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct vmci_transport_waiting_info {int dummy; } ;
struct vmci_handle {int dummy; } ;
struct TYPE_4__ {void* size; int /*<<< orphan*/  wait; void* mode; struct vmci_handle handle; } ;
struct TYPE_3__ {int payload_size; void* dst; void* src; } ;
struct vmci_transport_packet {int type; int /*<<< orphan*/  proto; TYPE_2__ u; int /*<<< orphan*/  _reserved2; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  version; TYPE_1__ dg; } ;
struct sockaddr_vm {int /*<<< orphan*/  svm_port; int /*<<< orphan*/  svm_cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMADDR_CID_ANY ; 
 int /*<<< orphan*/  VMCI_TRANSPORT_PACKET_RID ; 
#define  VMCI_TRANSPORT_PACKET_TYPE_ATTACH 140 
#define  VMCI_TRANSPORT_PACKET_TYPE_INVALID 139 
#define  VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE 138 
#define  VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE2 137 
#define  VMCI_TRANSPORT_PACKET_TYPE_OFFER 136 
#define  VMCI_TRANSPORT_PACKET_TYPE_READ 135 
#define  VMCI_TRANSPORT_PACKET_TYPE_REQUEST 134 
#define  VMCI_TRANSPORT_PACKET_TYPE_REQUEST2 133 
#define  VMCI_TRANSPORT_PACKET_TYPE_RST 132 
#define  VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN 131 
#define  VMCI_TRANSPORT_PACKET_TYPE_WAITING_READ 130 
#define  VMCI_TRANSPORT_PACKET_TYPE_WAITING_WRITE 129 
#define  VMCI_TRANSPORT_PACKET_TYPE_WROTE 128 
 int /*<<< orphan*/  VMCI_TRANSPORT_PACKET_VERSION ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct vmci_transport_waiting_info*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* vmci_make_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_transport_peer_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vmci_transport_packet_init(struct vmci_transport_packet *pkt,
			   struct sockaddr_vm *src,
			   struct sockaddr_vm *dst,
			   u8 type,
			   u64 size,
			   u64 mode,
			   struct vmci_transport_waiting_info *wait,
			   u16 proto,
			   struct vmci_handle handle)
{
	/* We register the stream control handler as an any cid handle so we
	 * must always send from a source address of VMADDR_CID_ANY
	 */
	pkt->dg.src = vmci_make_handle(VMADDR_CID_ANY,
				       VMCI_TRANSPORT_PACKET_RID);
	pkt->dg.dst = vmci_make_handle(dst->svm_cid,
				       vmci_transport_peer_rid(dst->svm_cid));
	pkt->dg.payload_size = sizeof(*pkt) - sizeof(pkt->dg);
	pkt->version = VMCI_TRANSPORT_PACKET_VERSION;
	pkt->type = type;
	pkt->src_port = src->svm_port;
	pkt->dst_port = dst->svm_port;
	memset(&pkt->proto, 0, sizeof(pkt->proto));
	memset(&pkt->_reserved2, 0, sizeof(pkt->_reserved2));

	switch (pkt->type) {
	case VMCI_TRANSPORT_PACKET_TYPE_INVALID:
		pkt->u.size = 0;
		break;

	case VMCI_TRANSPORT_PACKET_TYPE_REQUEST:
	case VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE:
		pkt->u.size = size;
		break;

	case VMCI_TRANSPORT_PACKET_TYPE_OFFER:
	case VMCI_TRANSPORT_PACKET_TYPE_ATTACH:
		pkt->u.handle = handle;
		break;

	case VMCI_TRANSPORT_PACKET_TYPE_WROTE:
	case VMCI_TRANSPORT_PACKET_TYPE_READ:
	case VMCI_TRANSPORT_PACKET_TYPE_RST:
		pkt->u.size = 0;
		break;

	case VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN:
		pkt->u.mode = mode;
		break;

	case VMCI_TRANSPORT_PACKET_TYPE_WAITING_READ:
	case VMCI_TRANSPORT_PACKET_TYPE_WAITING_WRITE:
		memcpy(&pkt->u.wait, wait, sizeof(pkt->u.wait));
		break;

	case VMCI_TRANSPORT_PACKET_TYPE_REQUEST2:
	case VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE2:
		pkt->u.size = size;
		pkt->proto = proto;
		break;
	}
}