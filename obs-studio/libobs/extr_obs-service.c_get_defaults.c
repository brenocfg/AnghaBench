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
struct obs_service_info {int /*<<< orphan*/  (* get_defaults ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline obs_data_t *get_defaults(const struct obs_service_info *info)
{
	obs_data_t *settings = obs_data_create();
	if (info->get_defaults)
		info->get_defaults(settings);
	return settings;
}