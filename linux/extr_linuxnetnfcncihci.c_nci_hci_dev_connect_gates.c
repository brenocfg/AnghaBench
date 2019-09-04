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
typedef  int /*<<< orphan*/  u8 ;
struct nci_hci_gate {int /*<<< orphan*/  pipe; int /*<<< orphan*/  gate; int /*<<< orphan*/  dest_host; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int nci_hci_connect_gate (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nci_hci_dev_connect_gates(struct nci_dev *ndev,
				     u8 gate_count,
				     struct nci_hci_gate *gates)
{
	int r;

	while (gate_count--) {
		r = nci_hci_connect_gate(ndev, gates->dest_host,
					 gates->gate, gates->pipe);
		if (r < 0)
			return r;
		gates++;
	}

	return 0;
}