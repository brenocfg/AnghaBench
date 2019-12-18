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
struct ip_vs_protocol {char const* (* state_name ) (unsigned int) ;} ;
struct ip_vs_conn {unsigned int state; int flags; scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_IP ; 
 int IP_VS_CONN_F_TEMPLATE ; 
 unsigned int IP_VS_CTPL_S_LAST ; 
 scalar_t__* ip_vs_ctpl_state_name_table ; 
 struct ip_vs_protocol* ip_vs_proto_get (scalar_t__) ; 
 char const* stub1 (unsigned int) ; 

const char *ip_vs_state_name(const struct ip_vs_conn *cp)
{
	unsigned int state = cp->state;
	struct ip_vs_protocol *pp;

	if (cp->flags & IP_VS_CONN_F_TEMPLATE) {

		if (state >= IP_VS_CTPL_S_LAST)
			return "ERR!";
		return ip_vs_ctpl_state_name_table[state] ? : "?";
	}
	pp = ip_vs_proto_get(cp->protocol);
	if (pp == NULL || pp->state_name == NULL)
		return (cp->protocol == IPPROTO_IP) ? "NONE" : "ERR!";
	return pp->state_name(state);
}