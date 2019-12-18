#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ is_available; int size; } ;
typedef  TYPE_1__* MCB_P ;
typedef  int /*<<< orphan*/  MCB ;

/* Variables and functions */
 scalar_t__ FREE ; 
 int /*<<< orphan*/  allocated_mem ; 
 int /*<<< orphan*/  mcb_count ; 

void r_free(void *p) {
	/* Mark in MCB that this chunk is free */
	MCB_P ptr = (MCB_P)p;
	ptr--;

	if (ptr->is_available != FREE) {
		mcb_count--;
		ptr->is_available = FREE;
		allocated_mem -= (ptr->size - sizeof (MCB));
	 }
}