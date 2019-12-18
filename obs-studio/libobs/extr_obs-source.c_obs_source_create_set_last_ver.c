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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_source_create_internal (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

obs_source_t *obs_source_create_set_last_ver(const char *id, const char *name,
					     obs_data_t *settings,
					     obs_data_t *hotkey_data,
					     uint32_t last_obs_ver)
{
	return obs_source_create_internal(id, name, settings, hotkey_data,
					  false, last_obs_ver);
}