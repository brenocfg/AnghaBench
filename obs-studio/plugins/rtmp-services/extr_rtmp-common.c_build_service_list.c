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
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_services (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  obs_property_list_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void build_service_list(obs_property_t *list, json_t *root,
			       bool show_all, const char *cur_service)
{
	obs_property_list_clear(list);
	add_services(list, root, show_all, cur_service);
}