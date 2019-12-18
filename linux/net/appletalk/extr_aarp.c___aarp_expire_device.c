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
struct net_device {int dummy; } ;
struct aarp_entry {struct aarp_entry* next; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aarp_expire (struct aarp_entry*) ; 

__attribute__((used)) static void __aarp_expire_device(struct aarp_entry **n, struct net_device *dev)
{
	struct aarp_entry *t;

	while (*n)
		if ((*n)->dev == dev) {
			t = *n;
			*n = (*n)->next;
			__aarp_expire(t);
		} else
			n = &((*n)->next);
}