#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* key; int /*<<< orphan*/  txkey; } ;
struct TYPE_4__ {int /*<<< orphan*/  privacy_invoked; } ;
struct ks_wlan_private {TYPE_3__ wpa; TYPE_1__ reg; } ;
struct TYPE_5__ {int /*<<< orphan*/ * rx_seq; int /*<<< orphan*/  key_len; int /*<<< orphan*/ * key_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11_GMK1_TSC ; 
 int /*<<< orphan*/  DOT11_GMK2_TSC ; 
 int /*<<< orphan*/  DOT11_PMK_TSC ; 
 int /*<<< orphan*/  DOT11_PRIVACY_INVOKED ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_ID ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_VALUE1 ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_VALUE2 ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_VALUE3 ; 
 int /*<<< orphan*/  DOT11_WEP_DEFAULT_KEY_VALUE4 ; 
#define  SME_SET_FLAG 136 
#define  SME_SET_GMK1_TSC 135 
#define  SME_SET_GMK2_TSC 134 
#define  SME_SET_KEY1 133 
#define  SME_SET_KEY2 132 
#define  SME_SET_KEY3 131 
#define  SME_SET_KEY4 130 
#define  SME_SET_PMK_TSC 129 
#define  SME_SET_TXKEY 128 
 int /*<<< orphan*/  WPA_RX_SEQ_LEN ; 
 int /*<<< orphan*/  hostif_mib_set_request_bool (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_mib_set_request_int (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_mib_set_request_ostring (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void hostif_sme_set_key(struct ks_wlan_private *priv, int type)
{
	switch (type) {
	case SME_SET_FLAG:
		hostif_mib_set_request_bool(priv, DOT11_PRIVACY_INVOKED,
					    priv->reg.privacy_invoked);
		break;
	case SME_SET_TXKEY:
		hostif_mib_set_request_int(priv, DOT11_WEP_DEFAULT_KEY_ID,
					   priv->wpa.txkey);
		break;
	case SME_SET_KEY1:
		hostif_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE1,
					       &priv->wpa.key[0].key_val[0],
					       priv->wpa.key[0].key_len);
		break;
	case SME_SET_KEY2:
		hostif_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE2,
					       &priv->wpa.key[1].key_val[0],
					       priv->wpa.key[1].key_len);
		break;
	case SME_SET_KEY3:
		hostif_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE3,
					       &priv->wpa.key[2].key_val[0],
					       priv->wpa.key[2].key_len);
		break;
	case SME_SET_KEY4:
		hostif_mib_set_request_ostring(priv,
					       DOT11_WEP_DEFAULT_KEY_VALUE4,
					       &priv->wpa.key[3].key_val[0],
					       priv->wpa.key[3].key_len);
		break;
	case SME_SET_PMK_TSC:
		hostif_mib_set_request_ostring(priv, DOT11_PMK_TSC,
					       &priv->wpa.key[0].rx_seq[0],
					       WPA_RX_SEQ_LEN);
		break;
	case SME_SET_GMK1_TSC:
		hostif_mib_set_request_ostring(priv, DOT11_GMK1_TSC,
					       &priv->wpa.key[1].rx_seq[0],
					       WPA_RX_SEQ_LEN);
		break;
	case SME_SET_GMK2_TSC:
		hostif_mib_set_request_ostring(priv, DOT11_GMK2_TSC,
					       &priv->wpa.key[2].rx_seq[0],
					       WPA_RX_SEQ_LEN);
		break;
	}
}