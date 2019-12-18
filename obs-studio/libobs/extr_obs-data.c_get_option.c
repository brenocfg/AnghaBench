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
 struct obs_data_item* obs_data_item_byname (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_item_get_string (struct obs_data_item*) ; 
 int /*<<< orphan*/  obs_data_item_release (struct obs_data_item**) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool get_option(obs_data_t *data, const char **option)
{
	if (!option)
		return false;

	struct obs_data_item *opt = obs_data_item_byname(data, "option");
	if (!opt)
		return false;

	*option = obs_data_item_get_string(opt);
	obs_data_item_release(&opt);

	obs_data_release(data);

	return true;
}