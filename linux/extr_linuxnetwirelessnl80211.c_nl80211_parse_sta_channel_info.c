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
struct station_parameters {int supported_channels_len; int supported_oper_classes_len; void* supported_oper_classes; void* supported_channels; } ;
struct genl_info {scalar_t__* attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NL80211_ATTR_STA_SUPPORTED_CHANNELS ; 
 size_t NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES ; 
 void* nla_data (scalar_t__) ; 
 void* nla_len (scalar_t__) ; 

__attribute__((used)) static int nl80211_parse_sta_channel_info(struct genl_info *info,
				      struct station_parameters *params)
{
	if (info->attrs[NL80211_ATTR_STA_SUPPORTED_CHANNELS]) {
		params->supported_channels =
		     nla_data(info->attrs[NL80211_ATTR_STA_SUPPORTED_CHANNELS]);
		params->supported_channels_len =
		     nla_len(info->attrs[NL80211_ATTR_STA_SUPPORTED_CHANNELS]);
		/*
		 * Need to include at least one (first channel, number of
		 * channels) tuple for each subband, and must have proper
		 * tuples for the rest of the data as well.
		 */
		if (params->supported_channels_len < 2)
			return -EINVAL;
		if (params->supported_channels_len % 2)
			return -EINVAL;
	}

	if (info->attrs[NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES]) {
		params->supported_oper_classes =
		 nla_data(info->attrs[NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES]);
		params->supported_oper_classes_len =
		  nla_len(info->attrs[NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES]);
		/*
		 * The value of the Length field of the Supported Operating
		 * Classes element is between 2 and 253.
		 */
		if (params->supported_oper_classes_len < 2 ||
		    params->supported_oper_classes_len > 253)
			return -EINVAL;
	}
	return 0;
}