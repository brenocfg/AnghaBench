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
struct obs_data_item {int /*<<< orphan*/  autoselect_size; int /*<<< orphan*/  default_size; int /*<<< orphan*/  data_size; } ;

/* Variables and functions */
 void* get_data_ptr (struct obs_data_item*) ; 

__attribute__((used)) static inline void *get_item_data(struct obs_data_item *item)
{
	if (!item->data_size && !item->default_size && !item->autoselect_size)
		return NULL;
	return get_data_ptr(item);
}