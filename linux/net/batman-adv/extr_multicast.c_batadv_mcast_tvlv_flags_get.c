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
typedef  int u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  mcast_flags ;

/* Variables and functions */
 int BATADV_MCAST_WANT_ALL_IPV4 ; 
 int BATADV_MCAST_WANT_ALL_IPV6 ; 
 int BATADV_MCAST_WANT_NO_RTR4 ; 
 int BATADV_MCAST_WANT_NO_RTR6 ; 
 int BATADV_NO_FLAGS ; 

__attribute__((used)) static u8
batadv_mcast_tvlv_flags_get(bool enabled, void *tvlv_value, u16 tvlv_value_len)
{
	u8 mcast_flags = BATADV_NO_FLAGS;

	if (enabled && tvlv_value && tvlv_value_len >= sizeof(mcast_flags))
		mcast_flags = *(u8 *)tvlv_value;

	if (!enabled) {
		mcast_flags |= BATADV_MCAST_WANT_ALL_IPV4;
		mcast_flags |= BATADV_MCAST_WANT_ALL_IPV6;
	}

	/* remove redundant flags to avoid sending duplicate packets later */
	if (mcast_flags & BATADV_MCAST_WANT_ALL_IPV4)
		mcast_flags |= BATADV_MCAST_WANT_NO_RTR4;

	if (mcast_flags & BATADV_MCAST_WANT_ALL_IPV6)
		mcast_flags |= BATADV_MCAST_WANT_NO_RTR6;

	return mcast_flags;
}