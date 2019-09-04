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
struct mwifiex_private {int dummy; } ;
struct mwifiex_ds_encrypt_key {int key_len; int is_igtk_key; int is_current_wep_key; int pn_len; int is_rx_seq_valid; int key_disable; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  pn; int /*<<< orphan*/  key_material; int /*<<< orphan*/  key_index; } ;
struct key_params {scalar_t__ cipher; int seq_len; int /*<<< orphan*/  const* seq; } ;
typedef  int /*<<< orphan*/  encrypt_key ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ WLAN_CIPHER_SUITE_AES_CMAC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (struct mwifiex_ds_encrypt_key*,int /*<<< orphan*/ ,int) ; 
 int mwifiex_sec_ioctl_encrypt_key (struct mwifiex_private*,struct mwifiex_ds_encrypt_key*) ; 

int mwifiex_set_encode(struct mwifiex_private *priv, struct key_params *kp,
		       const u8 *key, int key_len, u8 key_index,
		       const u8 *mac_addr, int disable)
{
	struct mwifiex_ds_encrypt_key encrypt_key;

	memset(&encrypt_key, 0, sizeof(encrypt_key));
	encrypt_key.key_len = key_len;
	encrypt_key.key_index = key_index;

	if (kp && kp->cipher == WLAN_CIPHER_SUITE_AES_CMAC)
		encrypt_key.is_igtk_key = true;

	if (!disable) {
		if (key_len)
			memcpy(encrypt_key.key_material, key, key_len);
		else
			encrypt_key.is_current_wep_key = true;

		if (mac_addr)
			memcpy(encrypt_key.mac_addr, mac_addr, ETH_ALEN);
		if (kp && kp->seq && kp->seq_len) {
			memcpy(encrypt_key.pn, kp->seq, kp->seq_len);
			encrypt_key.pn_len = kp->seq_len;
			encrypt_key.is_rx_seq_valid = true;
		}
	} else {
		encrypt_key.key_disable = true;
		if (mac_addr)
			memcpy(encrypt_key.mac_addr, mac_addr, ETH_ALEN);
	}

	return mwifiex_sec_ioctl_encrypt_key(priv, &encrypt_key);
}