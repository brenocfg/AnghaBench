#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * private_settings; } ;
typedef  TYPE_1__ obs_sceneitem_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_ptr_valid (TYPE_1__*,char*) ; 

obs_data_t *obs_sceneitem_get_private_settings(obs_sceneitem_t *item)
{
	if (!obs_ptr_valid(item, "obs_sceneitem_get_private_settings"))
		return NULL;

	obs_data_addref(item->private_settings);
	return item->private_settings;
}