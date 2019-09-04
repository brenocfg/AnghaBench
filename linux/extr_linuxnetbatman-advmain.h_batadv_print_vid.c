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
 unsigned short BATADV_VLAN_HAS_TAG ; 
 unsigned short VLAN_VID_MASK ; 

__attribute__((used)) static inline int batadv_print_vid(unsigned short vid)
{
	if (vid & BATADV_VLAN_HAS_TAG)
		return (int)(vid & VLAN_VID_MASK);
	else
		return -1;
}