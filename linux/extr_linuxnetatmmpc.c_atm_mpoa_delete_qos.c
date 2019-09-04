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
struct atm_mpoa_qos {struct atm_mpoa_qos* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct atm_mpoa_qos*) ; 
 struct atm_mpoa_qos* qos_head ; 

int atm_mpoa_delete_qos(struct atm_mpoa_qos *entry)
{
	struct atm_mpoa_qos *curr;

	if (entry == NULL)
		return 0;
	if (entry == qos_head) {
		qos_head = qos_head->next;
		kfree(entry);
		return 1;
	}

	curr = qos_head;
	while (curr != NULL) {
		if (curr->next == entry) {
			curr->next = entry->next;
			kfree(entry);
			return 1;
		}
		curr = curr->next;
	}

	return 0;
}