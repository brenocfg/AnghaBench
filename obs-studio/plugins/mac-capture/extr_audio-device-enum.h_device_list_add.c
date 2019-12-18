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
struct device_list {int /*<<< orphan*/  items; } ;
struct device_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct device_item*) ; 
 int /*<<< orphan*/  memset (struct device_item*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void device_list_add(struct device_list *list,
				   struct device_item *item)
{
	da_push_back(list->items, item);
	memset(item, 0, sizeof(struct device_item));
}