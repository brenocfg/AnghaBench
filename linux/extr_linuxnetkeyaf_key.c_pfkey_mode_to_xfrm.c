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
#define  IPSEC_MODE_ANY 131 
#define  IPSEC_MODE_BEET 130 
#define  IPSEC_MODE_TRANSPORT 129 
#define  IPSEC_MODE_TUNNEL 128 
 int XFRM_MODE_BEET ; 
 int XFRM_MODE_TRANSPORT ; 
 int XFRM_MODE_TUNNEL ; 

__attribute__((used)) static inline int pfkey_mode_to_xfrm(int mode)
{
	switch(mode) {
	case IPSEC_MODE_ANY:	/*XXX*/
	case IPSEC_MODE_TRANSPORT:
		return XFRM_MODE_TRANSPORT;
	case IPSEC_MODE_TUNNEL:
		return XFRM_MODE_TUNNEL;
	case IPSEC_MODE_BEET:
		return XFRM_MODE_BEET;
	default:
		return -1;
	}
}