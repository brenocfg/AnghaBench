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
typedef  int u64 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mod_params; } ;
struct TYPE_3__ {int dma64; } ;

/* Variables and functions */
 int GET_RX_DESC_BUFF_ADDR (int*) ; 
 int GET_RX_DESC_OWN (int*) ; 
 int GET_RX_DESC_PKT_LEN (int*) ; 
 int /*<<< orphan*/  GET_TXBUFFER_DESC_ADDR_HIGH (int*,int,int) ; 
 int GET_TXBUFFER_DESC_ADDR_LOW (int*,int) ; 
 int GET_TX_DESC_OWN (int*) ; 
#define  HW_DESC_OWN 131 
#define  HW_DESC_RXBUFF_ADDR 130 
#define  HW_DESC_RXPKT_LEN 129 
#define  HW_DESC_TXBUFF_ADDR 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

u64 rtl92ee_get_desc(struct ieee80211_hw *hw,
		     u8 *pdesc, bool istx, u8 desc_name)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u64 ret = 0;
	bool dma64 = rtlpriv->cfg->mod_params->dma64;

	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			ret = GET_TX_DESC_OWN(pdesc);
			break;
		case HW_DESC_TXBUFF_ADDR:
			ret = GET_TXBUFFER_DESC_ADDR_LOW(pdesc, 1);
			ret |= (u64)GET_TXBUFFER_DESC_ADDR_HIGH(pdesc, 1,
								dma64) << 32;
			break;
		default:
			WARN_ONCE(true,
				  "rtl8192ee: ERR txdesc :%d not processed\n",
				  desc_name);
			break;
		}
	} else {
		switch (desc_name) {
		case HW_DESC_OWN:
			ret = GET_RX_DESC_OWN(pdesc);
			break;
		case HW_DESC_RXPKT_LEN:
			ret = GET_RX_DESC_PKT_LEN(pdesc);
			break;
		case HW_DESC_RXBUFF_ADDR:
			ret = GET_RX_DESC_BUFF_ADDR(pdesc);
			break;
		default:
			WARN_ONCE(true,
				  "rtl8192ee: ERR rxdesc :%d not processed\n",
				  desc_name);
			break;
		}
	}
	return ret;
}