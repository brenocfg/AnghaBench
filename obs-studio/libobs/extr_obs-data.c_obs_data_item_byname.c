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
struct obs_data_item {int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  struct obs_data_item obs_data_item_t ;

/* Variables and functions */
 struct obs_data_item* get_item (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 

obs_data_item_t *obs_data_item_byname(obs_data_t *data, const char *name)
{
	if (!data)
		return NULL;

	struct obs_data_item *item = get_item(data, name);
	if (item)
		os_atomic_inc_long(&item->ref);
	return item;
}