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
typedef  int u32 ;
struct efx_nic {int dummy; } ;
struct efx_filter_spec {int match_flags; int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  outer_vid; int /*<<< orphan*/  inner_vid; int /*<<< orphan*/  ether_type; int /*<<< orphan*/  loc_port; int /*<<< orphan*/  loc_mac; int /*<<< orphan*/  rem_port; int /*<<< orphan*/  rem_mac; int /*<<< orphan*/  loc_host; int /*<<< orphan*/  rem_host; } ;
typedef  int /*<<< orphan*/  outer_ip_proto ;
typedef  int /*<<< orphan*/  ether_type ;
typedef  enum efx_encap_type { ____Placeholder_efx_encap_type } efx_encap_type ;
typedef  int /*<<< orphan*/  efx_dword_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EFX_ENCAP_FLAG_IPV6 ; 
 int EFX_ENCAP_TYPES_MASK ; 
#define  EFX_ENCAP_TYPE_GENEVE 130 
#define  EFX_ENCAP_TYPE_NVGRE 129 
#define  EFX_ENCAP_TYPE_VXLAN 128 
 int EFX_FILTER_MATCH_ETHER_TYPE ; 
 int EFX_FILTER_MATCH_INNER_VID ; 
 int EFX_FILTER_MATCH_IP_PROTO ; 
 int EFX_FILTER_MATCH_LOC_HOST ; 
 int EFX_FILTER_MATCH_LOC_MAC ; 
 int EFX_FILTER_MATCH_LOC_MAC_IG ; 
 int EFX_FILTER_MATCH_LOC_PORT ; 
 int EFX_FILTER_MATCH_OUTER_VID ; 
 int EFX_FILTER_MATCH_REM_HOST ; 
 int EFX_FILTER_MATCH_REM_MAC ; 
 int EFX_FILTER_MATCH_REM_PORT ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  FILTER_OP_EXT_IN_VNI_OR_VSID ; 
 int /*<<< orphan*/  FILTER_OP_EXT_IN_VNI_TYPE ; 
 int /*<<< orphan*/  FILTER_OP_IN_DST_IP ; 
 int /*<<< orphan*/  FILTER_OP_IN_DST_MAC ; 
 int /*<<< orphan*/  FILTER_OP_IN_DST_PORT ; 
 int /*<<< orphan*/  FILTER_OP_IN_ETHER_TYPE ; 
 int /*<<< orphan*/  FILTER_OP_IN_INNER_VLAN ; 
 int /*<<< orphan*/  FILTER_OP_IN_IP_PROTO ; 
 int /*<<< orphan*/  FILTER_OP_IN_MATCH_FIELDS ; 
 int /*<<< orphan*/  FILTER_OP_IN_OP ; 
 int /*<<< orphan*/  FILTER_OP_IN_OUTER_VLAN ; 
 int /*<<< orphan*/  FILTER_OP_IN_SRC_IP ; 
 int /*<<< orphan*/  FILTER_OP_IN_SRC_MAC ; 
 int /*<<< orphan*/  FILTER_OP_IN_SRC_PORT ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  MCDI_POPULATE_DWORD_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_MCAST_DST_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_UCAST_DST_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_MCAST_DST_LBN ; 
 int MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_UCAST_DST_LBN ; 
 int /*<<< orphan*/  MC_CMD_FILTER_OP_EXT_IN_VNI_TYPE_GENEVE ; 
 int /*<<< orphan*/  MC_CMD_FILTER_OP_EXT_IN_VNI_TYPE_VXLAN ; 
 int MC_CMD_FILTER_OP_IN_DST_IP_LEN ; 
 int MC_CMD_FILTER_OP_IN_DST_MAC_LEN ; 
 int MC_CMD_FILTER_OP_IN_DST_PORT_LEN ; 
 int MC_CMD_FILTER_OP_IN_ETHER_TYPE_LEN ; 
 int MC_CMD_FILTER_OP_IN_INNER_VLAN_LEN ; 
 int MC_CMD_FILTER_OP_IN_IP_PROTO_LEN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_DST_IP_LBN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_DST_MAC_LBN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_DST_PORT_LBN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_ETHER_TYPE_LBN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_INNER_VLAN_LBN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_IP_PROTO_LBN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_OUTER_VLAN_LBN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_SRC_IP_LBN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_SRC_MAC_LBN ; 
 int MC_CMD_FILTER_OP_IN_MATCH_SRC_PORT_LBN ; 
 int MC_CMD_FILTER_OP_IN_OP_INSERT ; 
 int MC_CMD_FILTER_OP_IN_OP_SUBSCRIBE ; 
 int MC_CMD_FILTER_OP_IN_OUTER_VLAN_LEN ; 
 int MC_CMD_FILTER_OP_IN_SRC_IP_LEN ; 
 int MC_CMD_FILTER_OP_IN_SRC_MAC_LEN ; 
 int MC_CMD_FILTER_OP_IN_SRC_PORT_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ efx_ef10_filter_is_exclusive (struct efx_filter_spec const*) ; 
 int efx_filter_get_encap_type (struct efx_filter_spec const*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
efx_ef10_filter_push_prep_set_match_fields(struct efx_nic *efx,
					   const struct efx_filter_spec *spec,
					   efx_dword_t *inbuf)
{
	enum efx_encap_type encap_type = efx_filter_get_encap_type(spec);
	u32 match_fields = 0, uc_match, mc_match;

	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_OP,
		       efx_ef10_filter_is_exclusive(spec) ?
		       MC_CMD_FILTER_OP_IN_OP_INSERT :
		       MC_CMD_FILTER_OP_IN_OP_SUBSCRIBE);

	/* Convert match flags and values.  Unlike almost
	 * everything else in MCDI, these fields are in
	 * network byte order.
	 */
#define COPY_VALUE(value, mcdi_field)					     \
	do {							     \
		match_fields |=					     \
			1 << MC_CMD_FILTER_OP_IN_MATCH_ ##	     \
			mcdi_field ## _LBN;			     \
		BUILD_BUG_ON(					     \
			MC_CMD_FILTER_OP_IN_ ## mcdi_field ## _LEN < \
			sizeof(value));				     \
		memcpy(MCDI_PTR(inbuf, FILTER_OP_IN_ ##	mcdi_field), \
		       &value, sizeof(value));			     \
	} while (0)
#define COPY_FIELD(gen_flag, gen_field, mcdi_field)			     \
	if (spec->match_flags & EFX_FILTER_MATCH_ ## gen_flag) {     \
		COPY_VALUE(spec->gen_field, mcdi_field);	     \
	}
	/* Handle encap filters first.  They will always be mismatch
	 * (unknown UC or MC) filters
	 */
	if (encap_type) {
		/* ether_type and outer_ip_proto need to be variables
		 * because COPY_VALUE wants to memcpy them
		 */
		__be16 ether_type =
			htons(encap_type & EFX_ENCAP_FLAG_IPV6 ?
			      ETH_P_IPV6 : ETH_P_IP);
		u8 vni_type = MC_CMD_FILTER_OP_EXT_IN_VNI_TYPE_GENEVE;
		u8 outer_ip_proto;

		switch (encap_type & EFX_ENCAP_TYPES_MASK) {
		case EFX_ENCAP_TYPE_VXLAN:
			vni_type = MC_CMD_FILTER_OP_EXT_IN_VNI_TYPE_VXLAN;
			/* fallthrough */
		case EFX_ENCAP_TYPE_GENEVE:
			COPY_VALUE(ether_type, ETHER_TYPE);
			outer_ip_proto = IPPROTO_UDP;
			COPY_VALUE(outer_ip_proto, IP_PROTO);
			/* We always need to set the type field, even
			 * though we're not matching on the TNI.
			 */
			MCDI_POPULATE_DWORD_1(inbuf,
				FILTER_OP_EXT_IN_VNI_OR_VSID,
				FILTER_OP_EXT_IN_VNI_TYPE,
				vni_type);
			break;
		case EFX_ENCAP_TYPE_NVGRE:
			COPY_VALUE(ether_type, ETHER_TYPE);
			outer_ip_proto = IPPROTO_GRE;
			COPY_VALUE(outer_ip_proto, IP_PROTO);
			break;
		default:
			WARN_ON(1);
		}

		uc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_UCAST_DST_LBN;
		mc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_MCAST_DST_LBN;
	} else {
		uc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_UCAST_DST_LBN;
		mc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_MCAST_DST_LBN;
	}

	if (spec->match_flags & EFX_FILTER_MATCH_LOC_MAC_IG)
		match_fields |=
			is_multicast_ether_addr(spec->loc_mac) ?
			1 << mc_match :
			1 << uc_match;
	COPY_FIELD(REM_HOST, rem_host, SRC_IP);
	COPY_FIELD(LOC_HOST, loc_host, DST_IP);
	COPY_FIELD(REM_MAC, rem_mac, SRC_MAC);
	COPY_FIELD(REM_PORT, rem_port, SRC_PORT);
	COPY_FIELD(LOC_MAC, loc_mac, DST_MAC);
	COPY_FIELD(LOC_PORT, loc_port, DST_PORT);
	COPY_FIELD(ETHER_TYPE, ether_type, ETHER_TYPE);
	COPY_FIELD(INNER_VID, inner_vid, INNER_VLAN);
	COPY_FIELD(OUTER_VID, outer_vid, OUTER_VLAN);
	COPY_FIELD(IP_PROTO, ip_proto, IP_PROTO);
#undef COPY_FIELD
#undef COPY_VALUE
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_MATCH_FIELDS,
		       match_fields);
}