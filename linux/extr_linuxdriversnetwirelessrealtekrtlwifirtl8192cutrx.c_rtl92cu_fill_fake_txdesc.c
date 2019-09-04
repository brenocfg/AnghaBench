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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_RATE1M ; 
 int /*<<< orphan*/  QSLT_MGNT ; 
 int /*<<< orphan*/  RTL_TX_HEADER_SIZE ; 
 int /*<<< orphan*/  SET_TX_DESC_FIRST_SEG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HWSEQ_EN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LAST_SEG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_NAV_USE_HDR (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_OWN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_ID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_SIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_QUEUE_SEL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_RATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_USE_RATE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _rtl_tx_desc_checksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl92cu_fill_fake_txdesc(struct ieee80211_hw *hw, u8 * pDesc,
			      u32 buffer_len, bool bIsPsPoll)
{
	/* Clear all status */
	memset(pDesc, 0, RTL_TX_HEADER_SIZE);
	SET_TX_DESC_FIRST_SEG(pDesc, 1); /* bFirstSeg; */
	SET_TX_DESC_LAST_SEG(pDesc, 1); /* bLastSeg; */
	SET_TX_DESC_OFFSET(pDesc, RTL_TX_HEADER_SIZE); /* Offset = 32 */
	SET_TX_DESC_PKT_SIZE(pDesc, buffer_len); /* Buffer size + command hdr */
	SET_TX_DESC_QUEUE_SEL(pDesc, QSLT_MGNT); /* Fixed queue of Mgnt queue */
	/* Set NAVUSEHDR to prevent Ps-poll AId filed to be changed to error
	 * vlaue by Hw. */
	if (bIsPsPoll) {
		SET_TX_DESC_NAV_USE_HDR(pDesc, 1);
	} else {
		SET_TX_DESC_HWSEQ_EN(pDesc, 1); /* Hw set sequence number */
		SET_TX_DESC_PKT_ID(pDesc, 0x100); /* set bit3 to 1. */
	}
	SET_TX_DESC_USE_RATE(pDesc, 1); /* use data rate which is set by Sw */
	SET_TX_DESC_OWN(pDesc, 1);
	SET_TX_DESC_TX_RATE(pDesc, DESC_RATE1M);
	_rtl_tx_desc_checksum(pDesc);
}