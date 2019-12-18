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

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ kmalloc_verbose ; 
 int /*<<< orphan*/  nr_allocated ; 
 int /*<<< orphan*/  printf (char*,void*) ; 
 int /*<<< orphan*/  uatomic_dec (int /*<<< orphan*/ *) ; 

void kfree(void *p)
{
	if (!p)
		return;
	uatomic_dec(&nr_allocated);
	if (kmalloc_verbose)
		printf("Freeing %p to malloc\n", p);
	free(p);
}