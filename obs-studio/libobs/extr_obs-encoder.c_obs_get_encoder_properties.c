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
struct obs_encoder_info {int /*<<< orphan*/ * (* get_properties ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  type_data; int /*<<< orphan*/ * (* get_properties2 ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 struct obs_encoder_info* find_encoder (char const*) ; 
 int /*<<< orphan*/ * get_defaults (struct obs_encoder_info const*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_properties_apply_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *) ; 

obs_properties_t *obs_get_encoder_properties(const char *id)
{
	const struct obs_encoder_info *ei = find_encoder(id);
	if (ei && (ei->get_properties || ei->get_properties2)) {
		obs_data_t *defaults = get_defaults(ei);
		obs_properties_t *properties = NULL;

		if (ei->get_properties2) {
			properties = ei->get_properties2(NULL, ei->type_data);
		} else if (ei->get_properties) {
			properties = ei->get_properties(NULL);
		}

		obs_properties_apply_settings(properties, defaults);
		obs_data_release(defaults);
		return properties;
	}
	return NULL;
}