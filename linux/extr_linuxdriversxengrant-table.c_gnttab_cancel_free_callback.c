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
struct gnttab_free_callback {struct gnttab_free_callback* next; } ;

/* Variables and functions */
 struct gnttab_free_callback* gnttab_free_callback_list ; 
 int /*<<< orphan*/  gnttab_list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void gnttab_cancel_free_callback(struct gnttab_free_callback *callback)
{
	struct gnttab_free_callback **pcb;
	unsigned long flags;

	spin_lock_irqsave(&gnttab_list_lock, flags);
	for (pcb = &gnttab_free_callback_list; *pcb; pcb = &(*pcb)->next) {
		if (*pcb == callback) {
			*pcb = callback->next;
			break;
		}
	}
	spin_unlock_irqrestore(&gnttab_list_lock, flags);
}