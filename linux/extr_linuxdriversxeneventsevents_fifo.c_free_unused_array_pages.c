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
 unsigned int MAX_EVENT_ARRAY_PAGES ; 
 int /*<<< orphan*/ ** event_array ; 
 unsigned int event_array_pages ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void free_unused_array_pages(void)
{
	unsigned i;

	for (i = event_array_pages; i < MAX_EVENT_ARRAY_PAGES; i++) {
		if (!event_array[i])
			break;
		free_page((unsigned long)event_array[i]);
		event_array[i] = NULL;
	}
}