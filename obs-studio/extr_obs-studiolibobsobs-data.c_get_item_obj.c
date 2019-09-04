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
 int /*<<< orphan*/ ** get_item_data (struct obs_data_item*) ; 

__attribute__((used)) static inline obs_data_t *get_item_obj(struct obs_data_item *item)
{
	if (!item)
		return NULL;

	obs_data_t **data = get_item_data(item);
	if (!data)
		return NULL;

	return *data;
}