#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct auth_body {scalar_t__ el_id; int /*<<< orphan*/  chall_text_len; int /*<<< orphan*/ * chall_text; int /*<<< orphan*/  alg; int /*<<< orphan*/  trans_seq; int /*<<< orphan*/  status; } ;
struct atmel_private {scalar_t__ ExpectedAuthentTransactionSeqNum; int CurrentAuthentTransactionSeqNum; int exclude_unencrypted; scalar_t__ station_is_associated; scalar_t__ AuthenticationRequestRetryCnt; scalar_t__ current_BSS; TYPE_1__* BSSinfo; scalar_t__ connect_to_any_BSS; scalar_t__ wep_is_on; scalar_t__ station_was_associated; scalar_t__ rx_buf; } ;
struct TYPE_2__ {int channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATION_STATE_ASSOCIATING ; 
 int /*<<< orphan*/  STATION_STATE_MGMT_ERROR ; 
 int /*<<< orphan*/  STATION_STATE_REASSOCIATING ; 
 scalar_t__ WLAN_AUTH_OPEN ; 
 scalar_t__ WLAN_AUTH_SHARED_KEY ; 
 scalar_t__ WLAN_EID_CHALLENGE ; 
 scalar_t__ WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG ; 
 scalar_t__ WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  atmel_enter_state (struct atmel_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_join_bss (struct atmel_private*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int retrieve_bss (struct atmel_private*) ; 
 int /*<<< orphan*/  send_association_request (struct atmel_private*,int) ; 
 int /*<<< orphan*/  send_authentication_request (struct atmel_private*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void authenticate(struct atmel_private *priv, u16 frame_len)
{
	struct auth_body *auth = (struct auth_body *)priv->rx_buf;
	u16 status = le16_to_cpu(auth->status);
	u16 trans_seq_no = le16_to_cpu(auth->trans_seq);
	u16 system = le16_to_cpu(auth->alg);

	if (status == WLAN_STATUS_SUCCESS && !priv->wep_is_on) {
		/* no WEP */
		if (priv->station_was_associated) {
			atmel_enter_state(priv, STATION_STATE_REASSOCIATING);
			send_association_request(priv, 1);
			return;
		} else {
			atmel_enter_state(priv, STATION_STATE_ASSOCIATING);
			send_association_request(priv, 0);
			return;
		}
	}

	if (status == WLAN_STATUS_SUCCESS && priv->wep_is_on) {
		int should_associate = 0;
		/* WEP */
		if (trans_seq_no != priv->ExpectedAuthentTransactionSeqNum)
			return;

		if (system == WLAN_AUTH_OPEN) {
			if (trans_seq_no == 0x0002) {
				should_associate = 1;
			}
		} else if (system == WLAN_AUTH_SHARED_KEY) {
			if (trans_seq_no == 0x0002 &&
			    auth->el_id == WLAN_EID_CHALLENGE) {
				send_authentication_request(priv, system, auth->chall_text, auth->chall_text_len);
				return;
			} else if (trans_seq_no == 0x0004) {
				should_associate = 1;
			}
		}

		if (should_associate) {
			if (priv->station_was_associated) {
				atmel_enter_state(priv, STATION_STATE_REASSOCIATING);
				send_association_request(priv, 1);
				return;
			} else {
				atmel_enter_state(priv, STATION_STATE_ASSOCIATING);
				send_association_request(priv, 0);
				return;
			}
		}
	}

	if (status == WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG) {
		/* Flip back and forth between WEP auth modes until the max
		 * authentication tries has been exceeded.
		 */
		if (system == WLAN_AUTH_OPEN) {
			priv->CurrentAuthentTransactionSeqNum = 0x001;
			priv->exclude_unencrypted = 1;
			send_authentication_request(priv, WLAN_AUTH_SHARED_KEY, NULL, 0);
			return;
		} else if (system == WLAN_AUTH_SHARED_KEY
			   && priv->wep_is_on) {
			priv->CurrentAuthentTransactionSeqNum = 0x001;
			priv->exclude_unencrypted = 0;
			send_authentication_request(priv, WLAN_AUTH_OPEN, NULL, 0);
			return;
		} else if (priv->connect_to_any_BSS) {
			int bss_index;

			priv->BSSinfo[(int)(priv->current_BSS)].channel |= 0x80;

			if ((bss_index  = retrieve_bss(priv)) != -1) {
				atmel_join_bss(priv, bss_index);
				return;
			}
		}
	}

	priv->AuthenticationRequestRetryCnt = 0;
	atmel_enter_state(priv,  STATION_STATE_MGMT_ERROR);
	priv->station_is_associated = 0;
}