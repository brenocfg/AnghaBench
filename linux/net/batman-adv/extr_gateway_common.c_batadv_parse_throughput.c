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
typedef  int u64 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
typedef  enum batadv_bandwidth_units { ____Placeholder_batadv_bandwidth_units } batadv_bandwidth_units ;

/* Variables and functions */
#define  BATADV_BW_UNIT_KBIT 129 
#define  BATADV_BW_UNIT_MBIT 128 
 int U32_MAX ; 
 int U64_MAX ; 
 int /*<<< orphan*/  batadv_err (struct net_device*,char*,char const*,char*) ; 
 int div_u64 (int,int) ; 
 int kstrtou64 (char*,int,int*) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

bool batadv_parse_throughput(struct net_device *net_dev, char *buff,
			     const char *description, u32 *throughput)
{
	enum batadv_bandwidth_units bw_unit_type = BATADV_BW_UNIT_KBIT;
	u64 lthroughput;
	char *tmp_ptr;
	int ret;

	if (strlen(buff) > 4) {
		tmp_ptr = buff + strlen(buff) - 4;

		if (strncasecmp(tmp_ptr, "mbit", 4) == 0)
			bw_unit_type = BATADV_BW_UNIT_MBIT;

		if (strncasecmp(tmp_ptr, "kbit", 4) == 0 ||
		    bw_unit_type == BATADV_BW_UNIT_MBIT)
			*tmp_ptr = '\0';
	}

	ret = kstrtou64(buff, 10, &lthroughput);
	if (ret) {
		batadv_err(net_dev,
			   "Invalid throughput speed for %s: %s\n",
			   description, buff);
		return false;
	}

	switch (bw_unit_type) {
	case BATADV_BW_UNIT_MBIT:
		/* prevent overflow */
		if (U64_MAX / 10 < lthroughput) {
			batadv_err(net_dev,
				   "Throughput speed for %s too large: %s\n",
				   description, buff);
			return false;
		}

		lthroughput *= 10;
		break;
	case BATADV_BW_UNIT_KBIT:
	default:
		lthroughput = div_u64(lthroughput, 100);
		break;
	}

	if (lthroughput > U32_MAX) {
		batadv_err(net_dev,
			   "Throughput speed for %s too large: %s\n",
			   description, buff);
		return false;
	}

	*throughput = lthroughput;

	return true;
}