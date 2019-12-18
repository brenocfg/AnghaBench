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
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (void*) ;} ;

/* Variables and functions */
 TYPE_1__ alloc ; 
 int /*<<< orphan*/  num_allocs ; 
 int /*<<< orphan*/  os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void bfree(void *ptr)
{
	if (ptr)
		os_atomic_dec_long(&num_allocs);
	alloc.free(ptr);
}