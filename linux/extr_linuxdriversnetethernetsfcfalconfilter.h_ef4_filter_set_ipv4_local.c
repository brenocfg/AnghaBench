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
typedef  int /*<<< orphan*/  u8 ;
struct ef4_filter_spec {int match_flags; int /*<<< orphan*/  loc_port; int /*<<< orphan*/ * loc_host; int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  ether_type; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EF4_FILTER_MATCH_ETHER_TYPE ; 
 int EF4_FILTER_MATCH_IP_PROTO ; 
 int EF4_FILTER_MATCH_LOC_HOST ; 
 int EF4_FILTER_MATCH_LOC_PORT ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ef4_filter_set_ipv4_local(struct ef4_filter_spec *spec, u8 proto,
			  __be32 host, __be16 port)
{
	spec->match_flags |=
		EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_IP_PROTO |
		EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_LOC_PORT;
	spec->ether_type = htons(ETH_P_IP);
	spec->ip_proto = proto;
	spec->loc_host[0] = host;
	spec->loc_port = port;
	return 0;
}