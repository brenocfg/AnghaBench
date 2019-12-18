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
struct ipv6_devconf {int /*<<< orphan*/  ndisc_tclass; int /*<<< orphan*/  disable_policy; int /*<<< orphan*/  addr_gen_mode; int /*<<< orphan*/  enhanced_dad; int /*<<< orphan*/  seg6_require_hmac; int /*<<< orphan*/  seg6_enabled; int /*<<< orphan*/  keep_addr_on_down; int /*<<< orphan*/  drop_unsolicited_na; int /*<<< orphan*/  drop_unicast_in_l2_multicast; int /*<<< orphan*/  use_oif_addrs_only; int /*<<< orphan*/  ignore_routes_with_linkdown; int /*<<< orphan*/  accept_ra_mtu; int /*<<< orphan*/  accept_ra_from_local; int /*<<< orphan*/  suppress_frag_ndisc; int /*<<< orphan*/  ndisc_notify; int /*<<< orphan*/  force_tllao; int /*<<< orphan*/  accept_dad; int /*<<< orphan*/  disable_ipv6; int /*<<< orphan*/  mc_forwarding; int /*<<< orphan*/  use_optimistic; int /*<<< orphan*/  optimistic_dad; int /*<<< orphan*/  accept_source_route; int /*<<< orphan*/  proxy_ndp; int /*<<< orphan*/  accept_ra_rt_info_max_plen; int /*<<< orphan*/  accept_ra_rt_info_min_plen; int /*<<< orphan*/  rtr_probe_interval; int /*<<< orphan*/  accept_ra_rtr_pref; int /*<<< orphan*/  accept_ra_pinfo; int /*<<< orphan*/  accept_ra_min_hop_limit; int /*<<< orphan*/  accept_ra_defrtr; int /*<<< orphan*/  max_addresses; int /*<<< orphan*/  max_desync_factor; int /*<<< orphan*/  regen_max_retry; int /*<<< orphan*/  temp_prefered_lft; int /*<<< orphan*/  temp_valid_lft; int /*<<< orphan*/  use_tempaddr; int /*<<< orphan*/  mldv2_unsolicited_report_interval; int /*<<< orphan*/  mldv1_unsolicited_report_interval; int /*<<< orphan*/  force_mld_version; int /*<<< orphan*/  rtr_solicit_delay; int /*<<< orphan*/  rtr_solicit_max_interval; int /*<<< orphan*/  rtr_solicit_interval; int /*<<< orphan*/  rtr_solicits; int /*<<< orphan*/  dad_transmits; int /*<<< orphan*/  autoconf; int /*<<< orphan*/  accept_redirects; int /*<<< orphan*/  accept_ra; int /*<<< orphan*/  mtu6; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  forwarding; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t DEVCONF_ACCEPT_DAD ; 
 size_t DEVCONF_ACCEPT_RA ; 
 size_t DEVCONF_ACCEPT_RA_DEFRTR ; 
 size_t DEVCONF_ACCEPT_RA_FROM_LOCAL ; 
 size_t DEVCONF_ACCEPT_RA_MIN_HOP_LIMIT ; 
 size_t DEVCONF_ACCEPT_RA_MTU ; 
 size_t DEVCONF_ACCEPT_RA_PINFO ; 
 size_t DEVCONF_ACCEPT_RA_RTR_PREF ; 
 size_t DEVCONF_ACCEPT_RA_RT_INFO_MAX_PLEN ; 
 size_t DEVCONF_ACCEPT_RA_RT_INFO_MIN_PLEN ; 
 size_t DEVCONF_ACCEPT_REDIRECTS ; 
 size_t DEVCONF_ACCEPT_SOURCE_ROUTE ; 
 size_t DEVCONF_ADDR_GEN_MODE ; 
 size_t DEVCONF_AUTOCONF ; 
 size_t DEVCONF_DAD_TRANSMITS ; 
 size_t DEVCONF_DISABLE_IPV6 ; 
 size_t DEVCONF_DISABLE_POLICY ; 
 size_t DEVCONF_DROP_UNICAST_IN_L2_MULTICAST ; 
 size_t DEVCONF_DROP_UNSOLICITED_NA ; 
 size_t DEVCONF_ENHANCED_DAD ; 
 size_t DEVCONF_FORCE_MLD_VERSION ; 
 size_t DEVCONF_FORCE_TLLAO ; 
 size_t DEVCONF_FORWARDING ; 
 size_t DEVCONF_HOPLIMIT ; 
 size_t DEVCONF_IGNORE_ROUTES_WITH_LINKDOWN ; 
 size_t DEVCONF_KEEP_ADDR_ON_DOWN ; 
 int DEVCONF_MAX ; 
 size_t DEVCONF_MAX_ADDRESSES ; 
 size_t DEVCONF_MAX_DESYNC_FACTOR ; 
 size_t DEVCONF_MC_FORWARDING ; 
 size_t DEVCONF_MLDV1_UNSOLICITED_REPORT_INTERVAL ; 
 size_t DEVCONF_MLDV2_UNSOLICITED_REPORT_INTERVAL ; 
 size_t DEVCONF_MTU6 ; 
 size_t DEVCONF_NDISC_NOTIFY ; 
 size_t DEVCONF_NDISC_TCLASS ; 
 size_t DEVCONF_OPTIMISTIC_DAD ; 
 size_t DEVCONF_PROXY_NDP ; 
 size_t DEVCONF_REGEN_MAX_RETRY ; 
 size_t DEVCONF_RTR_PROBE_INTERVAL ; 
 size_t DEVCONF_RTR_SOLICITS ; 
 size_t DEVCONF_RTR_SOLICIT_DELAY ; 
 size_t DEVCONF_RTR_SOLICIT_INTERVAL ; 
 size_t DEVCONF_RTR_SOLICIT_MAX_INTERVAL ; 
 size_t DEVCONF_SEG6_ENABLED ; 
 size_t DEVCONF_SEG6_REQUIRE_HMAC ; 
 size_t DEVCONF_SUPPRESS_FRAG_NDISC ; 
 size_t DEVCONF_TEMP_PREFERED_LFT ; 
 size_t DEVCONF_TEMP_VALID_LFT ; 
 size_t DEVCONF_USE_OIF_ADDRS_ONLY ; 
 size_t DEVCONF_USE_OPTIMISTIC ; 
 size_t DEVCONF_USE_TEMPADDR ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ipv6_store_devconf(struct ipv6_devconf *cnf,
				__s32 *array, int bytes)
{
	BUG_ON(bytes < (DEVCONF_MAX * 4));

	memset(array, 0, bytes);
	array[DEVCONF_FORWARDING] = cnf->forwarding;
	array[DEVCONF_HOPLIMIT] = cnf->hop_limit;
	array[DEVCONF_MTU6] = cnf->mtu6;
	array[DEVCONF_ACCEPT_RA] = cnf->accept_ra;
	array[DEVCONF_ACCEPT_REDIRECTS] = cnf->accept_redirects;
	array[DEVCONF_AUTOCONF] = cnf->autoconf;
	array[DEVCONF_DAD_TRANSMITS] = cnf->dad_transmits;
	array[DEVCONF_RTR_SOLICITS] = cnf->rtr_solicits;
	array[DEVCONF_RTR_SOLICIT_INTERVAL] =
		jiffies_to_msecs(cnf->rtr_solicit_interval);
	array[DEVCONF_RTR_SOLICIT_MAX_INTERVAL] =
		jiffies_to_msecs(cnf->rtr_solicit_max_interval);
	array[DEVCONF_RTR_SOLICIT_DELAY] =
		jiffies_to_msecs(cnf->rtr_solicit_delay);
	array[DEVCONF_FORCE_MLD_VERSION] = cnf->force_mld_version;
	array[DEVCONF_MLDV1_UNSOLICITED_REPORT_INTERVAL] =
		jiffies_to_msecs(cnf->mldv1_unsolicited_report_interval);
	array[DEVCONF_MLDV2_UNSOLICITED_REPORT_INTERVAL] =
		jiffies_to_msecs(cnf->mldv2_unsolicited_report_interval);
	array[DEVCONF_USE_TEMPADDR] = cnf->use_tempaddr;
	array[DEVCONF_TEMP_VALID_LFT] = cnf->temp_valid_lft;
	array[DEVCONF_TEMP_PREFERED_LFT] = cnf->temp_prefered_lft;
	array[DEVCONF_REGEN_MAX_RETRY] = cnf->regen_max_retry;
	array[DEVCONF_MAX_DESYNC_FACTOR] = cnf->max_desync_factor;
	array[DEVCONF_MAX_ADDRESSES] = cnf->max_addresses;
	array[DEVCONF_ACCEPT_RA_DEFRTR] = cnf->accept_ra_defrtr;
	array[DEVCONF_ACCEPT_RA_MIN_HOP_LIMIT] = cnf->accept_ra_min_hop_limit;
	array[DEVCONF_ACCEPT_RA_PINFO] = cnf->accept_ra_pinfo;
#ifdef CONFIG_IPV6_ROUTER_PREF
	array[DEVCONF_ACCEPT_RA_RTR_PREF] = cnf->accept_ra_rtr_pref;
	array[DEVCONF_RTR_PROBE_INTERVAL] =
		jiffies_to_msecs(cnf->rtr_probe_interval);
#ifdef CONFIG_IPV6_ROUTE_INFO
	array[DEVCONF_ACCEPT_RA_RT_INFO_MIN_PLEN] = cnf->accept_ra_rt_info_min_plen;
	array[DEVCONF_ACCEPT_RA_RT_INFO_MAX_PLEN] = cnf->accept_ra_rt_info_max_plen;
#endif
#endif
	array[DEVCONF_PROXY_NDP] = cnf->proxy_ndp;
	array[DEVCONF_ACCEPT_SOURCE_ROUTE] = cnf->accept_source_route;
#ifdef CONFIG_IPV6_OPTIMISTIC_DAD
	array[DEVCONF_OPTIMISTIC_DAD] = cnf->optimistic_dad;
	array[DEVCONF_USE_OPTIMISTIC] = cnf->use_optimistic;
#endif
#ifdef CONFIG_IPV6_MROUTE
	array[DEVCONF_MC_FORWARDING] = cnf->mc_forwarding;
#endif
	array[DEVCONF_DISABLE_IPV6] = cnf->disable_ipv6;
	array[DEVCONF_ACCEPT_DAD] = cnf->accept_dad;
	array[DEVCONF_FORCE_TLLAO] = cnf->force_tllao;
	array[DEVCONF_NDISC_NOTIFY] = cnf->ndisc_notify;
	array[DEVCONF_SUPPRESS_FRAG_NDISC] = cnf->suppress_frag_ndisc;
	array[DEVCONF_ACCEPT_RA_FROM_LOCAL] = cnf->accept_ra_from_local;
	array[DEVCONF_ACCEPT_RA_MTU] = cnf->accept_ra_mtu;
	array[DEVCONF_IGNORE_ROUTES_WITH_LINKDOWN] = cnf->ignore_routes_with_linkdown;
	/* we omit DEVCONF_STABLE_SECRET for now */
	array[DEVCONF_USE_OIF_ADDRS_ONLY] = cnf->use_oif_addrs_only;
	array[DEVCONF_DROP_UNICAST_IN_L2_MULTICAST] = cnf->drop_unicast_in_l2_multicast;
	array[DEVCONF_DROP_UNSOLICITED_NA] = cnf->drop_unsolicited_na;
	array[DEVCONF_KEEP_ADDR_ON_DOWN] = cnf->keep_addr_on_down;
	array[DEVCONF_SEG6_ENABLED] = cnf->seg6_enabled;
#ifdef CONFIG_IPV6_SEG6_HMAC
	array[DEVCONF_SEG6_REQUIRE_HMAC] = cnf->seg6_require_hmac;
#endif
	array[DEVCONF_ENHANCED_DAD] = cnf->enhanced_dad;
	array[DEVCONF_ADDR_GEN_MODE] = cnf->addr_gen_mode;
	array[DEVCONF_DISABLE_POLICY] = cnf->disable_policy;
	array[DEVCONF_NDISC_TCLASS] = cnf->ndisc_tclass;
}