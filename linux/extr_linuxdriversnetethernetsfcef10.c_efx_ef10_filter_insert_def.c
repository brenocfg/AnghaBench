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
typedef  int u16 ;
struct efx_nic {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  rss_context; struct efx_ef10_nic_data* nic_data; } ;
struct efx_filter_spec {int dummy; } ;
struct efx_ef10_nic_data {int datapath_caps; int /*<<< orphan*/  workaround_26807; } ;
struct efx_ef10_filter_vlan {int* default_filters; int /*<<< orphan*/  vid; } ;
typedef  enum efx_filter_flags { ____Placeholder_efx_filter_flags } efx_filter_flags ;
typedef  enum efx_encap_type { ____Placeholder_efx_encap_type } efx_encap_type ;
typedef  enum efx_ef10_default_filters { ____Placeholder_efx_ef10_default_filters } efx_ef10_default_filters ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 size_t EFX_EF10_BCAST ; 
 int EFX_EF10_FILTER_ID_INVALID ; 
#define  EFX_EF10_GENEVE4_MCDEF 146 
#define  EFX_EF10_GENEVE4_UCDEF 145 
#define  EFX_EF10_GENEVE6_MCDEF 144 
#define  EFX_EF10_GENEVE6_UCDEF 143 
#define  EFX_EF10_MCDEF 142 
#define  EFX_EF10_NVGRE4_MCDEF 141 
#define  EFX_EF10_NVGRE4_UCDEF 140 
#define  EFX_EF10_NVGRE6_MCDEF 139 
#define  EFX_EF10_NVGRE6_UCDEF 138 
#define  EFX_EF10_UCDEF 137 
#define  EFX_EF10_VXLAN4_MCDEF 136 
#define  EFX_EF10_VXLAN4_UCDEF 135 
#define  EFX_EF10_VXLAN6_MCDEF 134 
#define  EFX_EF10_VXLAN6_UCDEF 133 
#define  EFX_ENCAP_FLAG_IPV6 132 
 int EFX_ENCAP_TYPES_MASK ; 
#define  EFX_ENCAP_TYPE_GENEVE 131 
#define  EFX_ENCAP_TYPE_NONE 130 
#define  EFX_ENCAP_TYPE_NVGRE 129 
#define  EFX_ENCAP_TYPE_VXLAN 128 
 int EFX_FILTER_FLAG_RX_RSS ; 
 int /*<<< orphan*/  EFX_FILTER_PRI_AUTO ; 
 int /*<<< orphan*/  EFX_FILTER_VID_UNSPEC ; 
 int /*<<< orphan*/  EFX_WARN_ON_PARANOID (int) ; 
 int EINVAL ; 
 int EPERM ; 
 int ETH_ALEN ; 
 int MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drv ; 
 void* efx_ef10_filter_get_unsafe_id (int) ; 
 int efx_ef10_filter_insert_locked (struct efx_nic*,struct efx_filter_spec*,int) ; 
 int /*<<< orphan*/  efx_ef10_filter_remove_unsafe (struct efx_nic*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  efx_filter_init_rx (struct efx_filter_spec*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_filter_set_encap_type (struct efx_filter_spec*,int) ; 
 int /*<<< orphan*/  efx_filter_set_eth_local (struct efx_filter_spec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_filter_set_mc_def (struct efx_filter_spec*) ; 
 int /*<<< orphan*/  efx_filter_set_uc_def (struct efx_filter_spec*) ; 
 scalar_t__ efx_rss_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_cond_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warn ; 

__attribute__((used)) static int efx_ef10_filter_insert_def(struct efx_nic *efx,
				      struct efx_ef10_filter_vlan *vlan,
				      enum efx_encap_type encap_type,
				      bool multicast, bool rollback)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	enum efx_filter_flags filter_flags;
	struct efx_filter_spec spec;
	u8 baddr[ETH_ALEN];
	int rc;
	u16 *id;

	filter_flags = efx_rss_active(&efx->rss_context) ? EFX_FILTER_FLAG_RX_RSS : 0;

	efx_filter_init_rx(&spec, EFX_FILTER_PRI_AUTO, filter_flags, 0);

	if (multicast)
		efx_filter_set_mc_def(&spec);
	else
		efx_filter_set_uc_def(&spec);

	if (encap_type) {
		if (nic_data->datapath_caps &
		    (1 << MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN))
			efx_filter_set_encap_type(&spec, encap_type);
		else
			/* don't insert encap filters on non-supporting
			 * platforms. ID will be left as INVALID.
			 */
			return 0;
	}

	if (vlan->vid != EFX_FILTER_VID_UNSPEC)
		efx_filter_set_eth_local(&spec, vlan->vid, NULL);

	rc = efx_ef10_filter_insert_locked(efx, &spec, true);
	if (rc < 0) {
		const char *um = multicast ? "Multicast" : "Unicast";
		const char *encap_name = "";
		const char *encap_ipv = "";

		if ((encap_type & EFX_ENCAP_TYPES_MASK) ==
		    EFX_ENCAP_TYPE_VXLAN)
			encap_name = "VXLAN ";
		else if ((encap_type & EFX_ENCAP_TYPES_MASK) ==
			 EFX_ENCAP_TYPE_NVGRE)
			encap_name = "NVGRE ";
		else if ((encap_type & EFX_ENCAP_TYPES_MASK) ==
			 EFX_ENCAP_TYPE_GENEVE)
			encap_name = "GENEVE ";
		if (encap_type & EFX_ENCAP_FLAG_IPV6)
			encap_ipv = "IPv6 ";
		else if (encap_type)
			encap_ipv = "IPv4 ";

		/* unprivileged functions can't insert mismatch filters
		 * for encapsulated or unicast traffic, so downgrade
		 * those warnings to debug.
		 */
		netif_cond_dbg(efx, drv, efx->net_dev,
			       rc == -EPERM && (encap_type || !multicast), warn,
			       "%s%s%s mismatch filter insert failed rc=%d\n",
			       encap_name, encap_ipv, um, rc);
	} else if (multicast) {
		/* mapping from encap types to default filter IDs (multicast) */
		static enum efx_ef10_default_filters map[] = {
			[EFX_ENCAP_TYPE_NONE] = EFX_EF10_MCDEF,
			[EFX_ENCAP_TYPE_VXLAN] = EFX_EF10_VXLAN4_MCDEF,
			[EFX_ENCAP_TYPE_NVGRE] = EFX_EF10_NVGRE4_MCDEF,
			[EFX_ENCAP_TYPE_GENEVE] = EFX_EF10_GENEVE4_MCDEF,
			[EFX_ENCAP_TYPE_VXLAN | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_VXLAN6_MCDEF,
			[EFX_ENCAP_TYPE_NVGRE | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_NVGRE6_MCDEF,
			[EFX_ENCAP_TYPE_GENEVE | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_GENEVE6_MCDEF,
		};

		/* quick bounds check (BCAST result impossible) */
		BUILD_BUG_ON(EFX_EF10_BCAST != 0);
		if (encap_type >= ARRAY_SIZE(map) || map[encap_type] == 0) {
			WARN_ON(1);
			return -EINVAL;
		}
		/* then follow map */
		id = &vlan->default_filters[map[encap_type]];

		EFX_WARN_ON_PARANOID(*id != EFX_EF10_FILTER_ID_INVALID);
		*id = efx_ef10_filter_get_unsafe_id(rc);
		if (!nic_data->workaround_26807 && !encap_type) {
			/* Also need an Ethernet broadcast filter */
			efx_filter_init_rx(&spec, EFX_FILTER_PRI_AUTO,
					   filter_flags, 0);
			eth_broadcast_addr(baddr);
			efx_filter_set_eth_local(&spec, vlan->vid, baddr);
			rc = efx_ef10_filter_insert_locked(efx, &spec, true);
			if (rc < 0) {
				netif_warn(efx, drv, efx->net_dev,
					   "Broadcast filter insert failed rc=%d\n",
					   rc);
				if (rollback) {
					/* Roll back the mc_def filter */
					efx_ef10_filter_remove_unsafe(
							efx, EFX_FILTER_PRI_AUTO,
							*id);
					*id = EFX_EF10_FILTER_ID_INVALID;
					return rc;
				}
			} else {
				EFX_WARN_ON_PARANOID(
					vlan->default_filters[EFX_EF10_BCAST] !=
					EFX_EF10_FILTER_ID_INVALID);
				vlan->default_filters[EFX_EF10_BCAST] =
					efx_ef10_filter_get_unsafe_id(rc);
			}
		}
		rc = 0;
	} else {
		/* mapping from encap types to default filter IDs (unicast) */
		static enum efx_ef10_default_filters map[] = {
			[EFX_ENCAP_TYPE_NONE] = EFX_EF10_UCDEF,
			[EFX_ENCAP_TYPE_VXLAN] = EFX_EF10_VXLAN4_UCDEF,
			[EFX_ENCAP_TYPE_NVGRE] = EFX_EF10_NVGRE4_UCDEF,
			[EFX_ENCAP_TYPE_GENEVE] = EFX_EF10_GENEVE4_UCDEF,
			[EFX_ENCAP_TYPE_VXLAN | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_VXLAN6_UCDEF,
			[EFX_ENCAP_TYPE_NVGRE | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_NVGRE6_UCDEF,
			[EFX_ENCAP_TYPE_GENEVE | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_GENEVE6_UCDEF,
		};

		/* quick bounds check (BCAST result impossible) */
		BUILD_BUG_ON(EFX_EF10_BCAST != 0);
		if (encap_type >= ARRAY_SIZE(map) || map[encap_type] == 0) {
			WARN_ON(1);
			return -EINVAL;
		}
		/* then follow map */
		id = &vlan->default_filters[map[encap_type]];
		EFX_WARN_ON_PARANOID(*id != EFX_EF10_FILTER_ID_INVALID);
		*id = rc;
		rc = 0;
	}
	return rc;
}