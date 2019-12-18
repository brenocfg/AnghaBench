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
typedef  int u8 ;
struct ieee80211_sub_if_data {int dummy; } ;
struct TYPE_3__ {int* variable; int /*<<< orphan*/  capab_info; } ;
struct TYPE_4__ {TYPE_1__ assoc_resp; } ;
struct ieee80211_mgmt {int* sa; int* da; TYPE_2__ u; } ;
struct ieee80211_mgd_assoc_data {int* fils_nonces; int /*<<< orphan*/  fils_kek_len; int /*<<< orphan*/  fils_kek; } ;

/* Variables and functions */
 size_t AES_BLOCK_SIZE ; 
 int EINVAL ; 
 size_t ETH_ALEN ; 
 size_t FILS_NONCE_LEN ; 
 int /*<<< orphan*/  WLAN_EID_EXT_FILS_SESSION ; 
 int aes_siv_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t,int,int const**,size_t*,int*) ; 
 int* cfg80211_find_ext_ie (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mlme_dbg (struct ieee80211_sub_if_data*,char*,int*) ; 

int fils_decrypt_assoc_resp(struct ieee80211_sub_if_data *sdata,
			    u8 *frame, size_t *frame_len,
			    struct ieee80211_mgd_assoc_data *assoc_data)
{
	struct ieee80211_mgmt *mgmt = (void *)frame;
	u8 *capab, *ies, *encr;
	const u8 *addr[5 + 1], *session;
	size_t len[5 + 1];
	int res;
	size_t crypt_len;

	if (*frame_len < 24 + 6)
		return -EINVAL;

	capab = (u8 *)&mgmt->u.assoc_resp.capab_info;
	ies = mgmt->u.assoc_resp.variable;
	session = cfg80211_find_ext_ie(WLAN_EID_EXT_FILS_SESSION,
				       ies, frame + *frame_len - ies);
	if (!session || session[1] != 1 + 8) {
		mlme_dbg(sdata,
			 "No (valid) FILS Session element in (Re)Association Response frame from %pM",
			 mgmt->sa);
		return -EINVAL;
	}
	/* decrypt after FILS Session element */
	encr = (u8 *)session + 2 + 1 + 8;

	/* AES-SIV AAD vectors */

	/* The AP's BSSID */
	addr[0] = mgmt->sa;
	len[0] = ETH_ALEN;
	/* The STA's MAC address */
	addr[1] = mgmt->da;
	len[1] = ETH_ALEN;
	/* The AP's nonce */
	addr[2] = &assoc_data->fils_nonces[FILS_NONCE_LEN];
	len[2] = FILS_NONCE_LEN;
	/* The STA's nonce */
	addr[3] = assoc_data->fils_nonces;
	len[3] = FILS_NONCE_LEN;
	/* The (Re)Association Response frame from the Capability Information
	 * field to the FILS Session element (both inclusive).
	 */
	addr[4] = capab;
	len[4] = encr - capab;

	crypt_len = frame + *frame_len - encr;
	if (crypt_len < AES_BLOCK_SIZE) {
		mlme_dbg(sdata,
			 "Not enough room for AES-SIV data after FILS Session element in (Re)Association Response frame from %pM",
			 mgmt->sa);
		return -EINVAL;
	}
	res = aes_siv_decrypt(assoc_data->fils_kek, assoc_data->fils_kek_len,
			      encr, crypt_len, 5, addr, len, encr);
	if (res != 0) {
		mlme_dbg(sdata,
			 "AES-SIV decryption of (Re)Association Response frame from %pM failed",
			 mgmt->sa);
		return res;
	}
	*frame_len -= AES_BLOCK_SIZE;
	return 0;
}