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
struct obs_source_info {int /*<<< orphan*/  (* get_defaults ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  type_data; int /*<<< orphan*/  (* get_defaults2 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline obs_data_t *get_defaults(const struct obs_source_info *info)
{
	obs_data_t *settings = obs_data_create();
	if (info->get_defaults2)
		info->get_defaults2(info->type_data, settings);
	else if (info->get_defaults)
		info->get_defaults(settings);
	return settings;
}