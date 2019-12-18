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
struct sk_buff {int dummy; } ;
struct sfq_slot {struct sk_buff* skblist_next; struct sk_buff* skblist_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct sfq_slot*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void slot_queue_init(struct sfq_slot *slot)
{
	memset(slot, 0, sizeof(*slot));
	slot->skblist_prev = slot->skblist_next = (struct sk_buff *)slot;
}