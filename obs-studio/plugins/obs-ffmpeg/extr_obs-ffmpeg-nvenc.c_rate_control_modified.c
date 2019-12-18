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
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 scalar_t__ astrcmpi (char const*,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_properties_get (int /*<<< orphan*/ *,char*) ; 
 size_t obs_property_list_item_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_property_list_item_disable (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  obs_property_set_visible (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool rate_control_modified(obs_properties_t *ppts, obs_property_t *p,
				  obs_data_t *settings)
{
	const char *rc = obs_data_get_string(settings, "rate_control");
	bool cqp = astrcmpi(rc, "CQP") == 0;
	bool vbr = astrcmpi(rc, "VBR") == 0;
	bool lossless = astrcmpi(rc, "lossless") == 0;
	size_t count;

	p = obs_properties_get(ppts, "bitrate");
	obs_property_set_visible(p, !cqp && !lossless);
	p = obs_properties_get(ppts, "max_bitrate");
	obs_property_set_visible(p, vbr);
	p = obs_properties_get(ppts, "cqp");
	obs_property_set_visible(p, cqp);

	p = obs_properties_get(ppts, "preset");
	count = obs_property_list_item_count(p);

	for (size_t i = 0; i < count; i++) {
		bool compatible = (i == 0 || i == 3);
		obs_property_list_item_disable(p, i, lossless && !compatible);
	}

	return true;
}