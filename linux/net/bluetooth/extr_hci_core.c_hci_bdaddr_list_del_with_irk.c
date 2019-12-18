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
struct list_head {int dummy; } ;
struct bdaddr_list_with_irk {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int ENOENT ; 
 int /*<<< orphan*/  bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_bdaddr_list_clear (struct list_head*) ; 
 struct bdaddr_list_with_irk* hci_bdaddr_list_lookup_with_irk (struct list_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bdaddr_list_with_irk*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

int hci_bdaddr_list_del_with_irk(struct list_head *list, bdaddr_t *bdaddr,
							u8 type)
{
	struct bdaddr_list_with_irk *entry;

	if (!bacmp(bdaddr, BDADDR_ANY)) {
		hci_bdaddr_list_clear(list);
		return 0;
	}

	entry = hci_bdaddr_list_lookup_with_irk(list, bdaddr, type);
	if (!entry)
		return -ENOENT;

	list_del(&entry->list);
	kfree(entry);

	return 0;
}