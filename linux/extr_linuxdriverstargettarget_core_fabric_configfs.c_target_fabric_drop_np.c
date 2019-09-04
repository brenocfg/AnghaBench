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
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 

__attribute__((used)) static void target_fabric_drop_np(
	struct config_group *group,
	struct config_item *item)
{
	/*
	 * struct se_tpg_np is released via target_fabric_np_base_release()
	 */
	config_item_put(item);
}