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
struct efx_filter_spec {int match_flags; void* rem_port; void** rem_host; void* loc_port; void** loc_host; int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  ether_type; } ;
typedef  void* __be32 ;
typedef  void* __be16 ;

/* Variables and functions */
 int EFX_FILTER_MATCH_ETHER_TYPE ; 
 int EFX_FILTER_MATCH_IP_PROTO ; 
 int EFX_FILTER_MATCH_LOC_HOST ; 
 int EFX_FILTER_MATCH_LOC_PORT ; 
 int EFX_FILTER_MATCH_REM_HOST ; 
 int EFX_FILTER_MATCH_REM_PORT ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
efx_filter_set_ipv4_full(struct efx_filter_spec *spec, u8 proto,
			 __be32 lhost, __be16 lport,
			 __be32 rhost, __be16 rport)
{
	spec->match_flags |=
		EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_IP_PROTO |
		EFX_FILTER_MATCH_LOC_HOST | EFX_FILTER_MATCH_LOC_PORT |
		EFX_FILTER_MATCH_REM_HOST | EFX_FILTER_MATCH_REM_PORT;
	spec->ether_type = htons(ETH_P_IP);
	spec->ip_proto = proto;
	spec->loc_host[0] = lhost;
	spec->loc_port = lport;
	spec->rem_host[0] = rhost;
	spec->rem_port = rport;
	return 0;
}