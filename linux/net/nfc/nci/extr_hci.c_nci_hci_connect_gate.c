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
typedef  size_t u8 ;
struct nci_dev {TYPE_2__* hci_dev; } ;
struct TYPE_4__ {size_t* gate2pipe; TYPE_1__* pipes; } ;
struct TYPE_3__ {size_t gate; size_t host; } ;

/* Variables and functions */
 int EADDRINUSE ; 
#define  NCI_HCI_ADMIN_GATE 129 
 size_t NCI_HCI_ADMIN_PIPE ; 
 size_t NCI_HCI_DO_NOT_OPEN_PIPE ; 
 size_t NCI_HCI_INVALID_PIPE ; 
#define  NCI_HCI_LINK_MGMT_GATE 128 
 size_t NCI_HCI_LINK_MGMT_PIPE ; 
 size_t nci_hci_create_pipe (struct nci_dev*,size_t,size_t,int*) ; 
 scalar_t__ nci_hci_delete_pipe (struct nci_dev*,size_t) ; 
 int nci_hci_open_pipe (struct nci_dev*,size_t) ; 

int nci_hci_connect_gate(struct nci_dev *ndev,
			 u8 dest_host, u8 dest_gate, u8 pipe)
{
	bool pipe_created = false;
	int r;

	if (pipe == NCI_HCI_DO_NOT_OPEN_PIPE)
		return 0;

	if (ndev->hci_dev->gate2pipe[dest_gate] != NCI_HCI_INVALID_PIPE)
		return -EADDRINUSE;

	if (pipe != NCI_HCI_INVALID_PIPE)
		goto open_pipe;

	switch (dest_gate) {
	case NCI_HCI_LINK_MGMT_GATE:
		pipe = NCI_HCI_LINK_MGMT_PIPE;
	break;
	case NCI_HCI_ADMIN_GATE:
		pipe = NCI_HCI_ADMIN_PIPE;
	break;
	default:
		pipe = nci_hci_create_pipe(ndev, dest_host, dest_gate, &r);
		if (pipe == NCI_HCI_INVALID_PIPE)
			return r;
		pipe_created = true;
		break;
	}

open_pipe:
	r = nci_hci_open_pipe(ndev, pipe);
	if (r < 0) {
		if (pipe_created) {
			if (nci_hci_delete_pipe(ndev, pipe) < 0) {
				/* TODO: Cannot clean by deleting pipe...
				 * -> inconsistent state
				 */
			}
		}
		return r;
	}

	ndev->hci_dev->pipes[pipe].gate = dest_gate;
	ndev->hci_dev->pipes[pipe].host = dest_host;
	ndev->hci_dev->gate2pipe[dest_gate] = pipe;

	return 0;
}