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
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u_int16_t ;

/* Variables and functions */
 scalar_t__ IPPROTO_DCCP ; 
 scalar_t__ IPPROTO_SCTP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ IPPROTO_UDPLITE ; 
 scalar_t__ XT_INV_PROTO ; 
 scalar_t__ XT_MULTIPORT_DESTINATION ; 
 scalar_t__ XT_MULTIPORT_EITHER ; 
 scalar_t__ XT_MULTIPORT_SOURCE ; 
 scalar_t__ XT_MULTI_PORTS ; 

__attribute__((used)) static inline bool
check(u_int16_t proto,
      u_int8_t ip_invflags,
      u_int8_t match_flags,
      u_int8_t count)
{
	/* Must specify supported protocol, no unknown flags or bad count */
	return (proto == IPPROTO_TCP || proto == IPPROTO_UDP
		|| proto == IPPROTO_UDPLITE
		|| proto == IPPROTO_SCTP || proto == IPPROTO_DCCP)
		&& !(ip_invflags & XT_INV_PROTO)
		&& (match_flags == XT_MULTIPORT_SOURCE
		    || match_flags == XT_MULTIPORT_DESTINATION
		    || match_flags == XT_MULTIPORT_EITHER)
		&& count <= XT_MULTI_PORTS;
}