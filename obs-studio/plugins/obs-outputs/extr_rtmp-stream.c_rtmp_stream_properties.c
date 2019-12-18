#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netif_saddr_item {char* addr; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {size_t num; struct netif_saddr_item* array; } ;
struct netif_saddr_data {TYPE_1__ addrs; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_COMBO_FORMAT_STRING ; 
 int /*<<< orphan*/  OBS_COMBO_TYPE_LIST ; 
 int /*<<< orphan*/  OPT_BIND_IP ; 
 int /*<<< orphan*/  OPT_DROP_THRESHOLD ; 
 int /*<<< orphan*/  OPT_LOWLATENCY_ENABLED ; 
 int /*<<< orphan*/  OPT_NEWSOCKETLOOP_ENABLED ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  netif_get_addrs (struct netif_saddr_data*) ; 
 int /*<<< orphan*/  netif_saddr_data_free (struct netif_saddr_data*) ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_add_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 
 int /*<<< orphan*/  obs_property_list_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static obs_properties_t *rtmp_stream_properties(void *unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t *props = obs_properties_create();
	struct netif_saddr_data addrs = {0};
	obs_property_t *p;

	obs_properties_add_int(props, OPT_DROP_THRESHOLD,
			       obs_module_text("RTMPStream.DropThreshold"), 200,
			       10000, 100);

	p = obs_properties_add_list(props, OPT_BIND_IP,
				    obs_module_text("RTMPStream.BindIP"),
				    OBS_COMBO_TYPE_LIST,
				    OBS_COMBO_FORMAT_STRING);

	obs_property_list_add_string(p, obs_module_text("Default"), "default");

	netif_get_addrs(&addrs);
	for (size_t i = 0; i < addrs.addrs.num; i++) {
		struct netif_saddr_item item = addrs.addrs.array[i];
		obs_property_list_add_string(p, item.name, item.addr);
	}
	netif_saddr_data_free(&addrs);

	obs_properties_add_bool(props, OPT_NEWSOCKETLOOP_ENABLED,
				obs_module_text("RTMPStream.NewSocketLoop"));
	obs_properties_add_bool(props, OPT_LOWLATENCY_ENABLED,
				obs_module_text("RTMPStream.LowLatencyMode"));

	return props;
}