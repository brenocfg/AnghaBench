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
struct aarp_entry {struct aarp_entry* next; int /*<<< orphan*/  expires_at; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aarp_expire (struct aarp_entry*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __aarp_expire_timer(struct aarp_entry **n)
{
	struct aarp_entry *t;

	while (*n)
		/* Expired ? */
		if (time_after(jiffies, (*n)->expires_at)) {
			t = *n;
			*n = (*n)->next;
			__aarp_expire(t);
		} else
			n = &((*n)->next);
}