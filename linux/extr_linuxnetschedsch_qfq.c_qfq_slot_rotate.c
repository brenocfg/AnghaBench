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
typedef  unsigned int u64 ;
struct qfq_group {unsigned int S; unsigned int slot_shift; unsigned int full_slots; unsigned int front; } ;

/* Variables and functions */
 unsigned int QFQ_MAX_SLOTS ; 

__attribute__((used)) static void qfq_slot_rotate(struct qfq_group *grp, u64 roundedS)
{
	unsigned int i = (grp->S - roundedS) >> grp->slot_shift;

	grp->full_slots <<= i;
	grp->front = (grp->front - i) % QFQ_MAX_SLOTS;
}