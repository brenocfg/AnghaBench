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
struct list_data {TYPE_1__ items; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  list_item_free (struct list_data*,scalar_t__) ; 

__attribute__((used)) static inline void list_data_free(struct list_data *data)
{
	for (size_t i = 0; i < data->items.num; i++)
		list_item_free(data, data->items.array + i);

	da_free(data->items);
}