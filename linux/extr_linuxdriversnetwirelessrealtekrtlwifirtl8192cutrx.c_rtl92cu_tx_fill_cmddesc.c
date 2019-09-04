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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DESC_RATE1M ; 
 int /*<<< orphan*/  QSLT_BEACON ; 
 int /*<<< orphan*/  RTL_TX_DESC_SIZE ; 
 int RTL_TX_HEADER_SIZE ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_FIRST_SEG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HWSEQ_EN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LAST_SEG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LINIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_MACID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OWN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_ID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_SIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_QUEUE_SEL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RATE_ID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_RATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_USE_RATE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92cu_tx_fill_cmddesc(struct ieee80211_hw *hw,
			     u8 *pdesc, bool firstseg,
			     bool lastseg, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 fw_queue = QSLT_BEACON;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;

	memset((void *)pdesc, 0, RTL_TX_HEADER_SIZE);
	if (firstseg)
		SET_TX_DESC_OFFSET(pdesc, RTL_TX_HEADER_SIZE);
	SET_TX_DESC_TX_RATE(pdesc, DESC_RATE1M);
	SET_TX_DESC_SEQ(pdesc, 0);
	SET_TX_DESC_LINIP(pdesc, 0);
	SET_TX_DESC_QUEUE_SEL(pdesc, fw_queue);
	SET_TX_DESC_FIRST_SEG(pdesc, 1);
	SET_TX_DESC_LAST_SEG(pdesc, 1);
	SET_TX_DESC_RATE_ID(pdesc, 7);
	SET_TX_DESC_MACID(pdesc, 0);
	SET_TX_DESC_OWN(pdesc, 1);
	SET_TX_DESC_PKT_SIZE(pdesc, (u16)skb->len);
	SET_TX_DESC_FIRST_SEG(pdesc, 1);
	SET_TX_DESC_LAST_SEG(pdesc, 1);
	SET_TX_DESC_OFFSET(pdesc, 0x20);
	SET_TX_DESC_USE_RATE(pdesc, 1);
	if (!ieee80211_is_data_qos(fc)) {
		SET_TX_DESC_HWSEQ_EN(pdesc, 1);
		SET_TX_DESC_PKT_ID(pdesc, 8);
	}
	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD, "H2C Tx Cmd Content",
		      pdesc, RTL_TX_DESC_SIZE);
}