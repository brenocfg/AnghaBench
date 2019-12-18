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
struct list_item {long long ll; double d; void* str; void* name; int /*<<< orphan*/ * member_0; } ;
struct list_data {scalar_t__ format; int /*<<< orphan*/  items; } ;

/* Variables and functions */
 scalar_t__ OBS_COMBO_FORMAT_FLOAT ; 
 scalar_t__ OBS_COMBO_FORMAT_INT ; 
 void* bstrdup (void const*) ; 
 int /*<<< orphan*/  da_insert (int /*<<< orphan*/ ,size_t,struct list_item*) ; 

__attribute__((used)) static void insert_item(struct list_data *data, size_t idx, const char *name,
			const void *val)
{
	struct list_item item = {NULL};
	item.name = bstrdup(name);

	if (data->format == OBS_COMBO_FORMAT_INT)
		item.ll = *(const long long *)val;
	else if (data->format == OBS_COMBO_FORMAT_FLOAT)
		item.d = *(const double *)val;
	else
		item.str = bstrdup(val);

	da_insert(data->items, idx, &item);
}