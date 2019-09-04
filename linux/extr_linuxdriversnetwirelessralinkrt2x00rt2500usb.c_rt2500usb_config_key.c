#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct rt2x00lib_crypto {scalar_t__ cmd; int cipher; int /*<<< orphan*/  key; } ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_key_conf {scalar_t__ cipher; scalar_t__ keyidx; int hw_key_idx; int /*<<< orphan*/  flags; } ;
typedef  enum cipher { ____Placeholder_cipher } cipher ;
struct TYPE_6__ {int bit_mask; } ;

/* Variables and functions */
 scalar_t__ DISABLE_KEY ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int IEEE80211_HEADER ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int /*<<< orphan*/  KEY_ENTRY (int) ; 
 scalar_t__ SET_KEY ; 
 int /*<<< orphan*/  TXRX_CSR0 ; 
 TYPE_1__ TXRX_CSR0_ALGORITHM ; 
 TYPE_1__ TXRX_CSR0_IV_OFFSET ; 
 TYPE_1__ TXRX_CSR0_KEY_ID ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 int ffz (int) ; 
 int /*<<< orphan*/  rt2500usb_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int rt2x00_get_field16 (int,TYPE_1__) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int*,TYPE_1__,int) ; 

__attribute__((used)) static int rt2500usb_config_key(struct rt2x00_dev *rt2x00dev,
				struct rt2x00lib_crypto *crypto,
				struct ieee80211_key_conf *key)
{
	u32 mask;
	u16 reg;
	enum cipher curr_cipher;

	if (crypto->cmd == SET_KEY) {
		/*
		 * Disallow to set WEP key other than with index 0,
		 * it is known that not work at least on some hardware.
		 * SW crypto will be used in that case.
		 */
		if ((key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
		     key->cipher == WLAN_CIPHER_SUITE_WEP104) &&
		    key->keyidx != 0)
			return -EOPNOTSUPP;

		/*
		 * Pairwise key will always be entry 0, but this
		 * could collide with a shared key on the same
		 * position...
		 */
		mask = TXRX_CSR0_KEY_ID.bit_mask;

		reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR0);
		curr_cipher = rt2x00_get_field16(reg, TXRX_CSR0_ALGORITHM);
		reg &= mask;

		if (reg && reg == mask)
			return -ENOSPC;

		reg = rt2x00_get_field16(reg, TXRX_CSR0_KEY_ID);

		key->hw_key_idx += reg ? ffz(reg) : 0;
		/*
		 * Hardware requires that all keys use the same cipher
		 * (e.g. TKIP-only, AES-only, but not TKIP+AES).
		 * If this is not the first key, compare the cipher with the
		 * first one and fall back to SW crypto if not the same.
		 */
		if (key->hw_key_idx > 0 && crypto->cipher != curr_cipher)
			return -EOPNOTSUPP;

		rt2500usb_register_multiwrite(rt2x00dev, KEY_ENTRY(key->hw_key_idx),
					      crypto->key, sizeof(crypto->key));

		/*
		 * The driver does not support the IV/EIV generation
		 * in hardware. However it demands the data to be provided
		 * both separately as well as inside the frame.
		 * We already provided the CONFIG_CRYPTO_COPY_IV to rt2x00lib
		 * to ensure rt2x00lib will not strip the data from the
		 * frame after the copy, now we must tell mac80211
		 * to generate the IV/EIV data.
		 */
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
	}

	/*
	 * TXRX_CSR0_KEY_ID contains only single-bit fields to indicate
	 * a particular key is valid.
	 */
	reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR0);
	rt2x00_set_field16(&reg, TXRX_CSR0_ALGORITHM, crypto->cipher);
	rt2x00_set_field16(&reg, TXRX_CSR0_IV_OFFSET, IEEE80211_HEADER);

	mask = rt2x00_get_field16(reg, TXRX_CSR0_KEY_ID);
	if (crypto->cmd == SET_KEY)
		mask |= 1 << key->hw_key_idx;
	else if (crypto->cmd == DISABLE_KEY)
		mask &= ~(1 << key->hw_key_idx);
	rt2x00_set_field16(&reg, TXRX_CSR0_KEY_ID, mask);
	rt2500usb_register_write(rt2x00dev, TXRX_CSR0, reg);

	return 0;
}