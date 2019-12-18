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
typedef  int __u32 ;

/* Variables and functions */
 unsigned char IFLA_XDP_DRV_PROG_ID ; 
 unsigned char IFLA_XDP_HW_PROG_ID ; 
 unsigned char IFLA_XDP_PROG_ID ; 
 unsigned char IFLA_XDP_SKB_PROG_ID ; 
 unsigned char IFLA_XDP_UNSPEC ; 
 unsigned char XDP_ATTACHED_MULTI ; 
 int XDP_FLAGS_DRV_MODE ; 
 int XDP_FLAGS_HW_MODE ; 
 int XDP_FLAGS_SKB_MODE ; 

__attribute__((used)) static unsigned char get_xdp_id_attr(unsigned char mode, __u32 flags)
{
	if (mode != XDP_ATTACHED_MULTI)
		return IFLA_XDP_PROG_ID;
	if (flags & XDP_FLAGS_DRV_MODE)
		return IFLA_XDP_DRV_PROG_ID;
	if (flags & XDP_FLAGS_HW_MODE)
		return IFLA_XDP_HW_PROG_ID;
	if (flags & XDP_FLAGS_SKB_MODE)
		return IFLA_XDP_SKB_PROG_ID;

	return IFLA_XDP_UNSPEC;
}