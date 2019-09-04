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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 struct obs_data_item* get_item (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  obs_data_item_detach (struct obs_data_item*) ; 
 int /*<<< orphan*/  obs_data_item_release (struct obs_data_item**) ; 

void obs_data_erase(obs_data_t *data, const char *name)
{
	struct obs_data_item *item = get_item(data, name);

	if (item) {
		obs_data_item_detach(item);
		obs_data_item_release(&item);
	}
}