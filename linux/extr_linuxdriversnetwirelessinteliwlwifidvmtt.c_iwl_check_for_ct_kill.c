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
struct iwl_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_tt_enter_ct_kill (struct iwl_priv*) ; 
 scalar_t__ iwl_within_ct_kill_margin (struct iwl_priv*) ; 

bool iwl_check_for_ct_kill(struct iwl_priv *priv)
{
	bool is_ct_kill = false;

	if (iwl_within_ct_kill_margin(priv)) {
		iwl_tt_enter_ct_kill(priv);
		is_ct_kill = true;
	}
	return is_ct_kill;
}