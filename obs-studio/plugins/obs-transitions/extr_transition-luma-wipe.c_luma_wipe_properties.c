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
struct luma_wipe_info {int /*<<< orphan*/  wipes_list; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  S_LUMA_IMG ; 
 int /*<<< orphan*/  S_LUMA_INV ; 
 int /*<<< orphan*/  S_LUMA_SOFT ; 
 int /*<<< orphan*/  T_LUMA_IMG ; 
 int /*<<< orphan*/  T_LUMA_INV ; 
 int /*<<< orphan*/  T_LUMA_SOFT ; 
 int /*<<< orphan*/ * obs_data_first (int /*<<< orphan*/ ) ; 
 char* obs_data_item_get_name (int /*<<< orphan*/ *) ; 
 char* obs_data_item_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_item_next (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  obs_module_text (char const*) ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_float (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static obs_properties_t *luma_wipe_properties(void *data)
{
	obs_properties_t *props = obs_properties_create();
	struct luma_wipe_info *lwipe = data;

	obs_property_t *p;

	p = obs_properties_add_list(props, S_LUMA_IMG, T_LUMA_IMG,
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);

	obs_data_item_t *item = obs_data_first(lwipe->wipes_list);

	for (; item != NULL; obs_data_item_next(&item)) {
		const char *name = obs_data_item_get_name(item);
		const char *path = obs_data_item_get_string(item);
		obs_property_list_add_string(p, obs_module_text(name), path);
	}

	obs_properties_add_float(props, S_LUMA_SOFT, T_LUMA_SOFT, 0.0, 1.0,
				 0.05);
	obs_properties_add_bool(props, S_LUMA_INV, T_LUMA_INV);

	return props;
}