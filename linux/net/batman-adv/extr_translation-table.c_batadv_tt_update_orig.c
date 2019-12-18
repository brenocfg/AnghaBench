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
typedef  int /*<<< orphan*/  u16 ;
struct batadv_tvlv_tt_vlan_data {int dummy; } ;
struct batadv_tvlv_tt_change {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  orig; int /*<<< orphan*/  tt_lock; int /*<<< orphan*/  capa_initialized; int /*<<< orphan*/  last_ttvn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_TT ; 
 int /*<<< orphan*/  BATADV_ORIG_CAPA_HAS_TT ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_send_tt_request (struct batadv_priv*,struct batadv_orig_node*,int,struct batadv_tvlv_tt_vlan_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  batadv_tt_global_check_crc (struct batadv_orig_node*,struct batadv_tvlv_tt_vlan_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tt_global_update_crc (struct batadv_priv*,struct batadv_orig_node*) ; 
 int /*<<< orphan*/  batadv_tt_update_changes (struct batadv_priv*,struct batadv_orig_node*,int /*<<< orphan*/ ,int,struct batadv_tvlv_tt_change*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_tt_update_orig(struct batadv_priv *bat_priv,
				  struct batadv_orig_node *orig_node,
				  const void *tt_buff, u16 tt_num_vlan,
				  struct batadv_tvlv_tt_change *tt_change,
				  u16 tt_num_changes, u8 ttvn)
{
	u8 orig_ttvn = (u8)atomic_read(&orig_node->last_ttvn);
	struct batadv_tvlv_tt_vlan_data *tt_vlan;
	bool full_table = true;
	bool has_tt_init;

	tt_vlan = (struct batadv_tvlv_tt_vlan_data *)tt_buff;
	has_tt_init = test_bit(BATADV_ORIG_CAPA_HAS_TT,
			       &orig_node->capa_initialized);

	/* orig table not initialised AND first diff is in the OGM OR the ttvn
	 * increased by one -> we can apply the attached changes
	 */
	if ((!has_tt_init && ttvn == 1) || ttvn - orig_ttvn == 1) {
		/* the OGM could not contain the changes due to their size or
		 * because they have already been sent BATADV_TT_OGM_APPEND_MAX
		 * times.
		 * In this case send a tt request
		 */
		if (!tt_num_changes) {
			full_table = false;
			goto request_table;
		}

		spin_lock_bh(&orig_node->tt_lock);

		batadv_tt_update_changes(bat_priv, orig_node, tt_num_changes,
					 ttvn, tt_change);

		/* Even if we received the precomputed crc with the OGM, we
		 * prefer to recompute it to spot any possible inconsistency
		 * in the global table
		 */
		batadv_tt_global_update_crc(bat_priv, orig_node);

		spin_unlock_bh(&orig_node->tt_lock);

		/* The ttvn alone is not enough to guarantee consistency
		 * because a single value could represent different states
		 * (due to the wrap around). Thus a node has to check whether
		 * the resulting table (after applying the changes) is still
		 * consistent or not. E.g. a node could disconnect while its
		 * ttvn is X and reconnect on ttvn = X + TTVN_MAX: in this case
		 * checking the CRC value is mandatory to detect the
		 * inconsistency
		 */
		if (!batadv_tt_global_check_crc(orig_node, tt_vlan,
						tt_num_vlan))
			goto request_table;
	} else {
		/* if we missed more than one change or our tables are not
		 * in sync anymore -> request fresh tt data
		 */
		if (!has_tt_init || ttvn != orig_ttvn ||
		    !batadv_tt_global_check_crc(orig_node, tt_vlan,
						tt_num_vlan)) {
request_table:
			batadv_dbg(BATADV_DBG_TT, bat_priv,
				   "TT inconsistency for %pM. Need to retrieve the correct information (ttvn: %u last_ttvn: %u num_changes: %u)\n",
				   orig_node->orig, ttvn, orig_ttvn,
				   tt_num_changes);
			batadv_send_tt_request(bat_priv, orig_node, ttvn,
					       tt_vlan, tt_num_vlan,
					       full_table);
			return;
		}
	}
}