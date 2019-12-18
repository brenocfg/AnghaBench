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
struct obs_data {int dummy; } ;
typedef  int /*<<< orphan*/  obs_data_item_t ;
typedef  enum obs_data_type { ____Placeholder_obs_data_type } obs_data_type ;

/* Variables and functions */
 int /*<<< orphan*/ * get_item (struct obs_data*,char const*) ; 
 int /*<<< orphan*/  set_item_data (struct obs_data*,int /*<<< orphan*/ **,char const*,void const*,size_t,int,int,int) ; 

__attribute__((used)) static inline void set_item(struct obs_data *data, obs_data_item_t **item,
			    const char *name, const void *ptr, size_t size,
			    enum obs_data_type type)
{
	obs_data_item_t *actual_item = NULL;

	if (!data && !item)
		return;

	if (!item) {
		actual_item = get_item(data, name);
		item = &actual_item;
	}

	set_item_data(data, item, name, ptr, size, type, false, false);
}