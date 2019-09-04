#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct il_rxon_cmd {int filter_flags; scalar_t__ channel; int /*<<< orphan*/  bssid_addr; int /*<<< orphan*/  flags; } ;
struct il_priv {scalar_t__ switch_channel; int /*<<< orphan*/  tx_power_next; struct il_rxon_cmd staging; scalar_t__ start_calib; TYPE_2__* cfg; int /*<<< orphan*/  status; int /*<<< orphan*/  active; } ;
struct TYPE_4__ {TYPE_1__* mod_params; } ;
struct TYPE_3__ {int /*<<< orphan*/  sw_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_RXON ; 
 int /*<<< orphan*/  D_11H (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
 int RXON_FILTER_ASSOC_MSK ; 
 int /*<<< orphan*/  RXON_FLG_TSF2HOST_MSK ; 
 int /*<<< orphan*/  S_CHANNEL_SWITCH_PENDING ; 
 int /*<<< orphan*/  il4965_init_sensitivity (struct il_priv*) ; 
 int il4965_restore_default_wep_keys (struct il_priv*) ; 
 int il_check_rxon_cmd (struct il_priv*) ; 
 int /*<<< orphan*/  il_chswitch_done (struct il_priv*,int) ; 
 int /*<<< orphan*/  il_clear_ucode_stations (struct il_priv*) ; 
 int /*<<< orphan*/  il_full_rxon_required (struct il_priv*) ; 
 int /*<<< orphan*/  il_is_alive (struct il_priv*) ; 
 scalar_t__ il_is_associated (struct il_priv*) ; 
 int /*<<< orphan*/  il_print_rx_config_cmd (struct il_priv*) ; 
 int /*<<< orphan*/  il_restore_stations (struct il_priv*) ; 
 int il_send_cmd_pdu (struct il_priv*,int /*<<< orphan*/ ,int,struct il_rxon_cmd*) ; 
 int il_send_rxon_assoc (struct il_priv*) ; 
 int /*<<< orphan*/  il_set_rxon_hwcrypto (struct il_priv*,int) ; 
 int il_set_tx_power (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct il_rxon_cmd*,struct il_rxon_cmd*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il4965_commit_rxon(struct il_priv *il)
{
	/* cast away the const for active_rxon in this function */
	struct il_rxon_cmd *active_rxon = (void *)&il->active;
	int ret;
	bool new_assoc = !!(il->staging.filter_flags & RXON_FILTER_ASSOC_MSK);

	if (!il_is_alive(il))
		return -EBUSY;

	/* always get timestamp with Rx frame */
	il->staging.flags |= RXON_FLG_TSF2HOST_MSK;

	ret = il_check_rxon_cmd(il);
	if (ret) {
		IL_ERR("Invalid RXON configuration.  Not committing.\n");
		return -EINVAL;
	}

	/*
	 * receive commit_rxon request
	 * abort any previous channel switch if still in process
	 */
	if (test_bit(S_CHANNEL_SWITCH_PENDING, &il->status) &&
	    il->switch_channel != il->staging.channel) {
		D_11H("abort channel switch on %d\n",
		      le16_to_cpu(il->switch_channel));
		il_chswitch_done(il, false);
	}

	/* If we don't need to send a full RXON, we can use
	 * il_rxon_assoc_cmd which is used to reconfigure filter
	 * and other flags for the current radio configuration. */
	if (!il_full_rxon_required(il)) {
		ret = il_send_rxon_assoc(il);
		if (ret) {
			IL_ERR("Error setting RXON_ASSOC (%d)\n", ret);
			return ret;
		}

		memcpy(active_rxon, &il->staging, sizeof(*active_rxon));
		il_print_rx_config_cmd(il);
		/*
		 * We do not commit tx power settings while channel changing,
		 * do it now if tx power changed.
		 */
		il_set_tx_power(il, il->tx_power_next, false);
		return 0;
	}

	/* If we are currently associated and the new config requires
	 * an RXON_ASSOC and the new config wants the associated mask enabled,
	 * we must clear the associated from the active configuration
	 * before we apply the new config */
	if (il_is_associated(il) && new_assoc) {
		D_INFO("Toggling associated bit on current RXON\n");
		active_rxon->filter_flags &= ~RXON_FILTER_ASSOC_MSK;

		ret =
		    il_send_cmd_pdu(il, C_RXON,
				    sizeof(struct il_rxon_cmd), active_rxon);

		/* If the mask clearing failed then we set
		 * active_rxon back to what it was previously */
		if (ret) {
			active_rxon->filter_flags |= RXON_FILTER_ASSOC_MSK;
			IL_ERR("Error clearing ASSOC_MSK (%d)\n", ret);
			return ret;
		}
		il_clear_ucode_stations(il);
		il_restore_stations(il);
		ret = il4965_restore_default_wep_keys(il);
		if (ret) {
			IL_ERR("Failed to restore WEP keys (%d)\n", ret);
			return ret;
		}
	}

	D_INFO("Sending RXON\n" "* with%s RXON_FILTER_ASSOC_MSK\n"
	       "* channel = %d\n" "* bssid = %pM\n", (new_assoc ? "" : "out"),
	       le16_to_cpu(il->staging.channel), il->staging.bssid_addr);

	il_set_rxon_hwcrypto(il, !il->cfg->mod_params->sw_crypto);

	/* Apply the new configuration
	 * RXON unassoc clears the station table in uCode so restoration of
	 * stations is needed after it (the RXON command) completes
	 */
	if (!new_assoc) {
		ret =
		    il_send_cmd_pdu(il, C_RXON,
				    sizeof(struct il_rxon_cmd), &il->staging);
		if (ret) {
			IL_ERR("Error setting new RXON (%d)\n", ret);
			return ret;
		}
		D_INFO("Return from !new_assoc RXON.\n");
		memcpy(active_rxon, &il->staging, sizeof(*active_rxon));
		il_clear_ucode_stations(il);
		il_restore_stations(il);
		ret = il4965_restore_default_wep_keys(il);
		if (ret) {
			IL_ERR("Failed to restore WEP keys (%d)\n", ret);
			return ret;
		}
	}
	if (new_assoc) {
		il->start_calib = 0;
		/* Apply the new configuration
		 * RXON assoc doesn't clear the station table in uCode,
		 */
		ret =
		    il_send_cmd_pdu(il, C_RXON,
				    sizeof(struct il_rxon_cmd), &il->staging);
		if (ret) {
			IL_ERR("Error setting new RXON (%d)\n", ret);
			return ret;
		}
		memcpy(active_rxon, &il->staging, sizeof(*active_rxon));
	}
	il_print_rx_config_cmd(il);

	il4965_init_sensitivity(il);

	/* If we issue a new RXON command which required a tune then we must
	 * send a new TXPOWER command or we won't be able to Tx any frames */
	ret = il_set_tx_power(il, il->tx_power_next, true);
	if (ret) {
		IL_ERR("Error sending TX power (%d)\n", ret);
		return ret;
	}

	return 0;
}