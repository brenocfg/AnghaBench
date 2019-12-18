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
typedef  int /*<<< orphan*/  u16 ;
struct batadv_tvlv_tt_change {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  last_ttvn; } ;

/* Variables and functions */
 int /*<<< orphan*/  _batadv_tt_update_changes (struct batadv_priv*,struct batadv_orig_node*,struct batadv_tvlv_tt_change*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tt_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tt_save_orig_buffer (struct batadv_priv*,struct batadv_orig_node*,struct batadv_tvlv_tt_change*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_tt_update_changes(struct batadv_priv *bat_priv,
				     struct batadv_orig_node *orig_node,
				     u16 tt_num_changes, u8 ttvn,
				     struct batadv_tvlv_tt_change *tt_change)
{
	_batadv_tt_update_changes(bat_priv, orig_node, tt_change,
				  tt_num_changes, ttvn);

	batadv_tt_save_orig_buffer(bat_priv, orig_node, tt_change,
				   batadv_tt_len(tt_num_changes));
	atomic_set(&orig_node->last_ttvn, ttvn);
}