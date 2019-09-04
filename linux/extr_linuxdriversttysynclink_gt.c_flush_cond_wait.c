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
struct cond_wait {struct cond_wait* next; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_cond_wait(struct cond_wait **head)
{
	while (*head != NULL) {
		wake_up_interruptible(&(*head)->q);
		*head = (*head)->next;
	}
}