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
 unsigned char RATR_INX_WIRELESS_B ; 
 unsigned char RATR_INX_WIRELESS_G ; 
 unsigned char RATR_INX_WIRELESS_GB ; 
 unsigned char RATR_INX_WIRELESS_N ; 
 unsigned char RATR_INX_WIRELESS_NG ; 
 unsigned char RATR_INX_WIRELESS_NGB ; 
#define  WIRELESS_11A 136 
#define  WIRELESS_11A_5N 135 
#define  WIRELESS_11B 134 
#define  WIRELESS_11BG 133 
#define  WIRELESS_11BG_24N 132 
#define  WIRELESS_11G 131 
#define  WIRELESS_11G_24N 130 
#define  WIRELESS_11_24N 129 
#define  WIRELESS_11_5N 128 

unsigned char networktype_to_raid(unsigned char network_type)
{
	switch (network_type) {
	case WIRELESS_11B:
		return RATR_INX_WIRELESS_B;
	case WIRELESS_11A:
	case WIRELESS_11G:
		return RATR_INX_WIRELESS_G;
	case WIRELESS_11BG:
		return RATR_INX_WIRELESS_GB;
	case WIRELESS_11_24N:
	case WIRELESS_11_5N:
		return RATR_INX_WIRELESS_N;
	case WIRELESS_11A_5N:
	case WIRELESS_11G_24N:
		return  RATR_INX_WIRELESS_NG;
	case WIRELESS_11BG_24N:
		return RATR_INX_WIRELESS_NGB;
	default:
		return RATR_INX_WIRELESS_GB;
	}
}