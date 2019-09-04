#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int pkt_len; } ;
struct TYPE_5__ {scalar_t__ rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int uint ;
typedef  unsigned char u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct mlme_ext_priv {scalar_t__ mgnt_80211w_IPN_rx; } ;
struct ieee80211_hdr {unsigned char frame_control; unsigned char* addr1; } ;
struct TYPE_8__ {size_t dot11wBIPKeyid; TYPE_3__* dot11wBIPKey; } ;
struct adapter {TYPE_4__ securitypriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  unsigned char __le64 ;
typedef  unsigned char __le16 ;
struct TYPE_7__ {int /*<<< orphan*/  skey; } ;

/* Variables and functions */
 int BIP_AAD_SIZE ; 
 int /*<<< orphan*/  ClearMData (unsigned char*) ; 
 int /*<<< orphan*/  ClearPwrMgt (unsigned char*) ; 
 int /*<<< orphan*/  ClearRetry (unsigned char*) ; 
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  RTW_RX_HANDLED ; 
 int WLAN_HDR_A3_LEN ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _MME_IE_ ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 size_t le16_to_cpu (unsigned char) ; 
 scalar_t__ le64_to_cpu (unsigned char) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ omac1_aes_128 (int /*<<< orphan*/ ,unsigned char*,int,unsigned char*) ; 
 unsigned char* rtw_get_ie (unsigned char*,int /*<<< orphan*/ ,int*,int) ; 
 unsigned char* rtw_zmalloc (int) ; 

u32 rtw_BIP_verify(struct adapter *padapter, u8 *precvframe)
{
	struct rx_pkt_attrib *pattrib = &((union recv_frame *)precvframe)->u.hdr.attrib;
	u8 *pframe;
	u8 *BIP_AAD, *p;
	u32 res = _FAIL;
	uint len, ori_len;
	struct ieee80211_hdr *pwlanhdr;
	u8 mic[16];
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	__le16 le_tmp;
	__le64 le_tmp64;

	ori_len = pattrib->pkt_len-WLAN_HDR_A3_LEN+BIP_AAD_SIZE;
	BIP_AAD = rtw_zmalloc(ori_len);

	if (BIP_AAD == NULL) {
		DBG_871X("BIP AAD allocate fail\n");
		return _FAIL;
	}
	/* PKT start */
	pframe = (unsigned char *)((union recv_frame *)precvframe)->u.hdr.rx_data;
	/* mapping to wlan header */
	pwlanhdr = (struct ieee80211_hdr *)pframe;
	/* save the frame body + MME */
	memcpy(BIP_AAD+BIP_AAD_SIZE, pframe+WLAN_HDR_A3_LEN, pattrib->pkt_len-WLAN_HDR_A3_LEN);
	/* find MME IE pointer */
	p = rtw_get_ie(BIP_AAD+BIP_AAD_SIZE, _MME_IE_, &len, pattrib->pkt_len-WLAN_HDR_A3_LEN);
	/* Baron */
	if (p) {
		u16 keyid = 0;
		u64 temp_ipn = 0;
		/* save packet number */
		memcpy(&le_tmp64, p+4, 6);
		temp_ipn = le64_to_cpu(le_tmp64);
		/* BIP packet number should bigger than previous BIP packet */
		if (temp_ipn <= pmlmeext->mgnt_80211w_IPN_rx) {
			DBG_871X("replay BIP packet\n");
			goto BIP_exit;
		}
		/* copy key index */
		memcpy(&le_tmp, p+2, 2);
		keyid = le16_to_cpu(le_tmp);
		if (keyid != padapter->securitypriv.dot11wBIPKeyid) {
			DBG_871X("BIP key index error!\n");
			goto BIP_exit;
		}
		/* clear the MIC field of MME to zero */
		memset(p+2+len-8, 0, 8);

		/* conscruct AAD, copy frame control field */
		memcpy(BIP_AAD, &pwlanhdr->frame_control, 2);
		ClearRetry(BIP_AAD);
		ClearPwrMgt(BIP_AAD);
		ClearMData(BIP_AAD);
		/* conscruct AAD, copy address 1 to address 3 */
		memcpy(BIP_AAD+2, pwlanhdr->addr1, 18);

		if (omac1_aes_128(padapter->securitypriv.dot11wBIPKey[padapter->securitypriv.dot11wBIPKeyid].skey
			, BIP_AAD, ori_len, mic))
			goto BIP_exit;

		/* MIC field should be last 8 bytes of packet (packet without FCS) */
		if (!memcmp(mic, pframe+pattrib->pkt_len-8, 8)) {
			pmlmeext->mgnt_80211w_IPN_rx = temp_ipn;
			res = _SUCCESS;
		} else
			DBG_871X("BIP MIC error!\n");

	} else
		res = RTW_RX_HANDLED;
BIP_exit:

	kfree(BIP_AAD);
	return res;
}