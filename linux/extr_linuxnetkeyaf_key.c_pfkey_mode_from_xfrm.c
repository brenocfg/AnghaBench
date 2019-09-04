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
 int IPSEC_MODE_BEET ; 
 int IPSEC_MODE_TRANSPORT ; 
 int IPSEC_MODE_TUNNEL ; 
#define  XFRM_MODE_BEET 130 
#define  XFRM_MODE_TRANSPORT 129 
#define  XFRM_MODE_TUNNEL 128 

__attribute__((used)) static inline int pfkey_mode_from_xfrm(int mode)
{
	switch(mode) {
	case XFRM_MODE_TRANSPORT:
		return IPSEC_MODE_TRANSPORT;
	case XFRM_MODE_TUNNEL:
		return IPSEC_MODE_TUNNEL;
	case XFRM_MODE_BEET:
		return IPSEC_MODE_BEET;
	default:
		return -1;
	}
}