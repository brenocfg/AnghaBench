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
struct smp_irk {int /*<<< orphan*/  rpa; int /*<<< orphan*/  val; int /*<<< orphan*/  list; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  identity_resolving_keys; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct smp_irk* hci_find_irk_by_addr (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct smp_irk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

struct smp_irk *hci_add_irk(struct hci_dev *hdev, bdaddr_t *bdaddr,
			    u8 addr_type, u8 val[16], bdaddr_t *rpa)
{
	struct smp_irk *irk;

	irk = hci_find_irk_by_addr(hdev, bdaddr, addr_type);
	if (!irk) {
		irk = kzalloc(sizeof(*irk), GFP_KERNEL);
		if (!irk)
			return NULL;

		bacpy(&irk->bdaddr, bdaddr);
		irk->addr_type = addr_type;

		list_add_rcu(&irk->list, &hdev->identity_resolving_keys);
	}

	memcpy(irk->val, val, 16);
	bacpy(&irk->rpa, rpa);

	return irk;
}