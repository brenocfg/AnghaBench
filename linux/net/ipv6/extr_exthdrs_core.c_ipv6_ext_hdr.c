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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ NEXTHDR_AUTH ; 
 scalar_t__ NEXTHDR_DEST ; 
 scalar_t__ NEXTHDR_FRAGMENT ; 
 scalar_t__ NEXTHDR_HOP ; 
 scalar_t__ NEXTHDR_NONE ; 
 scalar_t__ NEXTHDR_ROUTING ; 

bool ipv6_ext_hdr(u8 nexthdr)
{
	/*
	 * find out if nexthdr is an extension header or a protocol
	 */
	return   (nexthdr == NEXTHDR_HOP)	||
		 (nexthdr == NEXTHDR_ROUTING)	||
		 (nexthdr == NEXTHDR_FRAGMENT)	||
		 (nexthdr == NEXTHDR_AUTH)	||
		 (nexthdr == NEXTHDR_NONE)	||
		 (nexthdr == NEXTHDR_DEST);
}