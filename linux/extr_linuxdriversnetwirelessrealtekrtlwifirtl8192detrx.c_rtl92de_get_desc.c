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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct rx_desc_92c {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_RX_DESC_OWN (struct rx_desc_92c*) ; 
 int /*<<< orphan*/  GET_RX_DESC_PKT_LEN (struct rx_desc_92c*) ; 
 int /*<<< orphan*/  GET_TX_DESC_OWN (int*) ; 
 int /*<<< orphan*/  GET_TX_DESC_TX_BUFFER_ADDRESS (int*) ; 
#define  HW_DESC_OWN 130 
#define  HW_DESC_RXPKT_LEN 129 
#define  HW_DESC_TXBUFF_ADDR 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

u64 rtl92de_get_desc(struct ieee80211_hw *hw,
		     u8 *p_desc, bool istx, u8 desc_name)
{
	u32 ret = 0;

	if (istx) {
		switch (desc_name) {
		case HW_DESC_OWN:
			ret = GET_TX_DESC_OWN(p_desc);
			break;
		case HW_DESC_TXBUFF_ADDR:
			ret = GET_TX_DESC_TX_BUFFER_ADDRESS(p_desc);
			break;
		default:
			WARN_ONCE(true, "rtl8192de: ERR txdesc :%d not processed\n",
				  desc_name);
			break;
		}
	} else {
		struct rx_desc_92c *pdesc = (struct rx_desc_92c *)p_desc;
		switch (desc_name) {
		case HW_DESC_OWN:
			ret = GET_RX_DESC_OWN(pdesc);
			break;
		case HW_DESC_RXPKT_LEN:
			ret = GET_RX_DESC_PKT_LEN(pdesc);
			break;
		default:
			WARN_ONCE(true, "rtl8192de: ERR rxdesc :%d not processed\n",
				  desc_name);
			break;
		}
	}
	return ret;
}