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
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_item_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_data_item_get_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_to_json (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void set_json_obj(json_t *json, const char *name,
				obs_data_item_t *item)
{
	obs_data_t *obj = obs_data_item_get_obj(item);
	json_object_set_new(json, name, obs_data_to_json(obj));
	obs_data_release(obj);
}