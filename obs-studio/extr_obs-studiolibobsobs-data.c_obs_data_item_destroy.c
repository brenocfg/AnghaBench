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

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct obs_data_item*) ; 
 int /*<<< orphan*/  item_autoselect_data_release (struct obs_data_item*) ; 
 int /*<<< orphan*/  item_data_release (struct obs_data_item*) ; 
 int /*<<< orphan*/  item_default_data_release (struct obs_data_item*) ; 
 int /*<<< orphan*/  obs_data_item_detach (struct obs_data_item*) ; 

__attribute__((used)) static inline void obs_data_item_destroy(struct obs_data_item *item)
{
	item_data_release(item);
	item_default_data_release(item);
	item_autoselect_data_release(item);
	obs_data_item_detach(item);
	bfree(item);
}