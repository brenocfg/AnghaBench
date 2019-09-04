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
struct obs_data_item {size_t name_len; size_t data_len; size_t default_len; size_t autoselect_size; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t obs_data_item_total_size(struct obs_data_item *item)
{
	return sizeof(struct obs_data_item) + item->name_len +
		item->data_len + item->default_len + item->autoselect_size;
}