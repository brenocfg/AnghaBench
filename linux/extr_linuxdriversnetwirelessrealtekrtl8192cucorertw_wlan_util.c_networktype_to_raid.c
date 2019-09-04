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
	unsigned char raid;

	switch(network_type)
	{
		case WIRELESS_11B:
			raid = 6;
			break;
		case WIRELESS_11A:
		case WIRELESS_11G:
			raid = 5;
			break;
		case WIRELESS_11BG:
			raid = 4;
			break;
		case WIRELESS_11_24N:
		case WIRELESS_11_5N:
			raid = 3;
			break;
		case WIRELESS_11A_5N:
		case WIRELESS_11G_24N:
			raid = 1;
			break;
		case WIRELESS_11BG_24N:
			raid = 0;
			break;
		default:
			raid = 4;
			break;	

	}

	return raid;
	
}