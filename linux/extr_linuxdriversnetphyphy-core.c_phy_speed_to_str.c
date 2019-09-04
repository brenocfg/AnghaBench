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

/* Variables and functions */
#define  SPEED_10 141 
#define  SPEED_100 140 
#define  SPEED_1000 139 
#define  SPEED_10000 138 
#define  SPEED_100000 137 
#define  SPEED_14000 136 
#define  SPEED_20000 135 
#define  SPEED_2500 134 
#define  SPEED_25000 133 
#define  SPEED_40000 132 
#define  SPEED_5000 131 
#define  SPEED_50000 130 
#define  SPEED_56000 129 
#define  SPEED_UNKNOWN 128 

const char *phy_speed_to_str(int speed)
{
	switch (speed) {
	case SPEED_10:
		return "10Mbps";
	case SPEED_100:
		return "100Mbps";
	case SPEED_1000:
		return "1Gbps";
	case SPEED_2500:
		return "2.5Gbps";
	case SPEED_5000:
		return "5Gbps";
	case SPEED_10000:
		return "10Gbps";
	case SPEED_14000:
		return "14Gbps";
	case SPEED_20000:
		return "20Gbps";
	case SPEED_25000:
		return "25Gbps";
	case SPEED_40000:
		return "40Gbps";
	case SPEED_50000:
		return "50Gbps";
	case SPEED_56000:
		return "56Gbps";
	case SPEED_100000:
		return "100Gbps";
	case SPEED_UNKNOWN:
		return "Unknown";
	default:
		return "Unsupported (update phy-core.c)";
	}
}