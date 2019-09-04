#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_qos_parameters {int dummy; } ;
struct TYPE_3__ {int ac_info; } ;
struct ieee80211_qos_parameter_info {TYPE_1__ info_element; } ;
struct ieee80211_qos_information_element {int ac_info; } ;
struct TYPE_4__ {int param_count; int supported; struct ieee80211_qos_parameters parameters; } ;
struct ieee80211_network {TYPE_2__ qos_data; int /*<<< orphan*/  flags; } ;
struct ieee80211_info_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DEBUG_QOS (char*) ; 
 int /*<<< orphan*/  NETWORK_HAS_QOS_INFORMATION ; 
 int /*<<< orphan*/  NETWORK_HAS_QOS_PARAMETERS ; 
 int /*<<< orphan*/  ieee80211_qos_convert_ac_to_parameters (struct ieee80211_qos_parameter_info*,struct ieee80211_qos_parameters*) ; 
 int ieee80211_read_qos_info_element (struct ieee80211_qos_information_element*,struct ieee80211_info_element*) ; 
 int ieee80211_read_qos_param_element (struct ieee80211_qos_parameter_info*,struct ieee80211_info_element*) ; 

__attribute__((used)) static int ieee80211_parse_qos_info_param_IE(struct ieee80211_info_element
					     *info_element,
					     struct ieee80211_network *network)
{
	int rc = 0;
	struct ieee80211_qos_parameters *qos_param = NULL;
	struct ieee80211_qos_information_element qos_info_element;

	rc = ieee80211_read_qos_info_element(&qos_info_element, info_element);

	if (rc == 0) {
		network->qos_data.param_count = qos_info_element.ac_info & 0x0F;
		network->flags |= NETWORK_HAS_QOS_INFORMATION;
	} else {
		struct ieee80211_qos_parameter_info param_element;

		rc = ieee80211_read_qos_param_element(&param_element,
						      info_element);
		if (rc == 0) {
			qos_param = &(network->qos_data.parameters);
			ieee80211_qos_convert_ac_to_parameters(&param_element,
							       qos_param);
			network->flags |= NETWORK_HAS_QOS_PARAMETERS;
			network->qos_data.param_count =
			    param_element.info_element.ac_info & 0x0F;
		}
	}

	if (rc == 0) {
		IEEE80211_DEBUG_QOS("QoS is supported\n");
		network->qos_data.supported = 1;
	}
	return rc;
}