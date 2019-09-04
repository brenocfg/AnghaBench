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
typedef  int u32 ;
struct efx_filter_spec {unsigned int match_flags; int /*<<< orphan*/  loc_mac; } ;
typedef  enum efx_encap_type { ____Placeholder_efx_encap_type } efx_encap_type ;

/* Variables and functions */
 unsigned int EFX_FILTER_MATCH_ENCAP_TYPE ; 
 unsigned int EFX_FILTER_MATCH_ETHER_TYPE ; 
 unsigned int EFX_FILTER_MATCH_INNER_VID ; 
 unsigned int EFX_FILTER_MATCH_IP_PROTO ; 
 unsigned int EFX_FILTER_MATCH_LOC_HOST ; 
 unsigned int EFX_FILTER_MATCH_LOC_MAC ; 
 unsigned int EFX_FILTER_MATCH_LOC_MAC_IG ; 
 unsigned int EFX_FILTER_MATCH_LOC_PORT ; 
 unsigned int EFX_FILTER_MATCH_OUTER_VID ; 
 unsigned int EFX_FILTER_MATCH_REM_HOST ; 
 unsigned int EFX_FILTER_MATCH_REM_MAC ; 
 unsigned int EFX_FILTER_MATCH_REM_PORT ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_DST_IP_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_DST_MAC_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_DST_PORT_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_ETHER_TYPE_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_DST_IP_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_DST_MAC_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_DST_PORT_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_ETHER_TYPE_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_INNER_VLAN_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_IP_PROTO_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_OUTER_VLAN_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_SRC_IP_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_SRC_MAC_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_SRC_PORT_LBN ; 
 unsigned int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_MCAST_DST_LBN ; 
 unsigned int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_UCAST_DST_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_INNER_VLAN_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IP_PROTO_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_OUTER_VLAN_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_SRC_IP_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_SRC_MAC_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_SRC_PORT_LBN ; 
 unsigned int MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_MCAST_DST_LBN ; 
 unsigned int MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_UCAST_DST_LBN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned int) ; 
 int efx_filter_get_encap_type (struct efx_filter_spec const*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 efx_ef10_filter_mcdi_flags_from_spec(const struct efx_filter_spec *spec)
{
	enum efx_encap_type encap_type = efx_filter_get_encap_type(spec);
	unsigned int match_flags = spec->match_flags;
	unsigned int uc_match, mc_match;
	u32 mcdi_flags = 0;

#define MAP_FILTER_TO_MCDI_FLAG(gen_flag, mcdi_field, encap) {		\
		unsigned int  old_match_flags = match_flags;		\
		match_flags &= ~EFX_FILTER_MATCH_ ## gen_flag;		\
		if (match_flags != old_match_flags)			\
			mcdi_flags |=					\
				(1 << ((encap) ?			\
				       MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_ ## \
				       mcdi_field ## _LBN :		\
				       MC_CMD_FILTER_OP_EXT_IN_MATCH_ ##\
				       mcdi_field ## _LBN));		\
	}
	/* inner or outer based on encap type */
	MAP_FILTER_TO_MCDI_FLAG(REM_HOST, SRC_IP, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(LOC_HOST, DST_IP, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(REM_MAC, SRC_MAC, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(REM_PORT, SRC_PORT, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(LOC_MAC, DST_MAC, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(LOC_PORT, DST_PORT, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(ETHER_TYPE, ETHER_TYPE, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(IP_PROTO, IP_PROTO, encap_type);
	/* always outer */
	MAP_FILTER_TO_MCDI_FLAG(INNER_VID, INNER_VLAN, false);
	MAP_FILTER_TO_MCDI_FLAG(OUTER_VID, OUTER_VLAN, false);
#undef MAP_FILTER_TO_MCDI_FLAG

	/* special handling for encap type, and mismatch */
	if (encap_type) {
		match_flags &= ~EFX_FILTER_MATCH_ENCAP_TYPE;
		mcdi_flags |=
			(1 << MC_CMD_FILTER_OP_EXT_IN_MATCH_ETHER_TYPE_LBN);
		mcdi_flags |= (1 << MC_CMD_FILTER_OP_EXT_IN_MATCH_IP_PROTO_LBN);

		uc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_UCAST_DST_LBN;
		mc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_MCAST_DST_LBN;
	} else {
		uc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_UCAST_DST_LBN;
		mc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_MCAST_DST_LBN;
	}

	if (match_flags & EFX_FILTER_MATCH_LOC_MAC_IG) {
		match_flags &= ~EFX_FILTER_MATCH_LOC_MAC_IG;
		mcdi_flags |=
			is_multicast_ether_addr(spec->loc_mac) ?
			1 << mc_match :
			1 << uc_match;
	}

	/* Did we map them all? */
	WARN_ON_ONCE(match_flags);

	return mcdi_flags;
}