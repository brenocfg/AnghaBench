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
struct aarp_entry {int /*<<< orphan*/  packet_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct aarp_entry*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __aarp_expire(struct aarp_entry *a)
{
	skb_queue_purge(&a->packet_queue);
	kfree(a);
}