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
typedef  int /*<<< orphan*/  obs_service_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_service_create_internal (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

obs_service_t *obs_service_create_private(const char *id, const char *name,
					  obs_data_t *settings)
{
	return obs_service_create_internal(id, name, settings, NULL, true);
}