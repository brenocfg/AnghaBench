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
struct obs_data_item {int dummy; } ;

/* Variables and functions */
 size_t base_get_alignment () ; 
 int strlen (char const*) ; 

__attribute__((used)) static inline size_t get_name_align_size(const char *name)
{
	size_t name_size = strlen(name) + 1;
	size_t alignment = base_get_alignment();
	size_t total_size;

	total_size = sizeof(struct obs_data_item) + (name_size + alignment - 1);
	total_size &= ~(alignment - 1);

	return total_size - sizeof(struct obs_data_item);
}