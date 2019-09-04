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
typedef  scalar_t__ u8 ;
struct registry_priv {int rf_config; int mp_mode; int wifi_test; int /*<<< orphan*/  low_power; int /*<<< orphan*/  vcs_type; int /*<<< orphan*/  vrtl_carrier_sense; int /*<<< orphan*/  cbw40_enable; } ;
struct fw_priv {int mp_mode; int turboMode; int /*<<< orphan*/  lowPowerMode; int /*<<< orphan*/  vcsMode; int /*<<< orphan*/  vcsType; int /*<<< orphan*/  rf_config; int /*<<< orphan*/  bw_40MHz_en; scalar_t__ usb_ep_num; int /*<<< orphan*/  hci_sel; } ;
struct dvobj_priv {scalar_t__ nr_endpoint; } ;
struct _adapter {struct registry_priv registrypriv; struct dvobj_priv dvobjpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8712_HCI_TYPE_72USB ; 
 int /*<<< orphan*/  RTL8712_RFC_1T1R ; 
 int /*<<< orphan*/  RTL8712_RFC_1T2R ; 
 int /*<<< orphan*/  RTL8712_RFC_2T2R ; 
#define  RTL8712_RF_1T1R 130 
#define  RTL8712_RF_1T2R 129 
#define  RTL8712_RF_2T2R 128 
 int /*<<< orphan*/  memset (struct fw_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_fwpriv(struct _adapter *padapter, struct fw_priv *pfwpriv)
{
	struct dvobj_priv *pdvobj = &padapter->dvobjpriv;
	struct registry_priv *pregpriv = &padapter->registrypriv;

	memset(pfwpriv, 0, sizeof(struct fw_priv));
	/* todo: check if needs endian conversion */
	pfwpriv->hci_sel =  RTL8712_HCI_TYPE_72USB;
	pfwpriv->usb_ep_num = (u8)pdvobj->nr_endpoint;
	pfwpriv->bw_40MHz_en = pregpriv->cbw40_enable;
	switch (pregpriv->rf_config) {
	case RTL8712_RF_1T1R:
		pfwpriv->rf_config = RTL8712_RFC_1T1R;
		break;
	case RTL8712_RF_2T2R:
		pfwpriv->rf_config = RTL8712_RFC_2T2R;
		break;
	case RTL8712_RF_1T2R:
	default:
		pfwpriv->rf_config = RTL8712_RFC_1T2R;
	}
	pfwpriv->mp_mode = (pregpriv->mp_mode == 1) ? 1 : 0;
	pfwpriv->vcsType = pregpriv->vrtl_carrier_sense; /* 0:off 1:on 2:auto */
	pfwpriv->vcsMode = pregpriv->vcs_type; /* 1:RTS/CTS 2:CTS to self */
	/* default enable turboMode */
	pfwpriv->turboMode = ((pregpriv->wifi_test == 1) ? 0 : 1);
	pfwpriv->lowPowerMode = pregpriv->low_power;
}