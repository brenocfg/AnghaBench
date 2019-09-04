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
 int /*<<< orphan*/  free_pages_exact (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pages_list_size (size_t) ; 

void optee_free_pages_list(void *list, size_t num_entries)
{
	free_pages_exact(list, get_pages_list_size(num_entries));
}