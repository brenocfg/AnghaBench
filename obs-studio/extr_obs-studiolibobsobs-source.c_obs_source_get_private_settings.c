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
typedef  TYPE_1__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_ptr_valid (TYPE_1__*,char*) ; 

obs_data_t *obs_source_get_private_settings(obs_source_t *source)
{
	if (!obs_ptr_valid(source, "obs_source_get_private_settings"))
		return NULL;

	obs_data_addref(source->private_settings);
	return source->private_settings;
}