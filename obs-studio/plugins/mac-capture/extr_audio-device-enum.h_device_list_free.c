#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct device_list {TYPE_1__ items; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  device_item_free (scalar_t__) ; 

__attribute__((used)) static inline void device_list_free(struct device_list *list)
{
	for (size_t i = 0; i < list->items.num; i++)
		device_item_free(list->items.array + i);

	da_free(list->items);
}