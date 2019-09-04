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
typedef  size_t uint ;
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_tx_rate {scalar_t__ count; } ;
struct TYPE_8__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {TYPE_4__ status; } ;
struct ieee80211_rts {void* duration; int /*<<< orphan*/  frame_control; } ;
struct d11txh {int* RTSPLCPFallback; int* FragPLCPFallback; void* MacTxControlHigh; void* RTSDurFallback; void* TxFesTimeFallback; void* TxFesTimeNormal; void* PreloadSize; void* MModeFbrLen; void* MModeLen; void* XtraFrameTypes; void* MacTxControlLow; int /*<<< orphan*/  rts_frame; void* TxFrameID; } ;
struct brcms_fifo_info {scalar_t__ dmaxferrate; int /*<<< orphan*/  ampdu_pld_size; } ;
struct brcms_c_info {TYPE_3__* pub; TYPE_2__* hw; TYPE_1__* band; struct ampdu_info* ampdu; } ;
struct brcms_ampdu_session {int dma_len; int ampdu_len; int /*<<< orphan*/  skb_list; struct brcms_c_info* wlc; } ;
struct ampdu_info {struct brcms_fifo_info* fifo_tb; } ;
struct TYPE_7__ {int /*<<< orphan*/  unit; } ;
struct TYPE_6__ {int /*<<< orphan*/  d11core; } ;
struct TYPE_5__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int AMPDU_DELIMITER_LEN ; 
 size_t AMPDU_FBR_NULL_DELIM ; 
 size_t BRCMS_GET_CCK_PLCP_LEN (int*) ; 
 size_t BRCMS_GET_MIMO_PLCP_LEN (int*) ; 
 int BRCMS_GF_PREAMBLE ; 
 int BRCMS_LONG_PREAMBLE ; 
 int BRCMS_MM_PREAMBLE ; 
 int /*<<< orphan*/  BRCMS_SET_MIMO_PLCP_AMPDU (int*) ; 
 int /*<<< orphan*/  BRCMS_SET_MIMO_PLCP_LEN (int*,int) ; 
 int BRCMS_SHORT_PREAMBLE ; 
 scalar_t__ CHSPEC_SB_UPPER (int /*<<< orphan*/ ) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int MIMO_PLCP_40MHZ ; 
 int PHY_TXC1_BW_20MHZ ; 
 int PHY_TXC1_BW_20MHZ_UP ; 
 int PHY_TXC1_BW_40MHZ ; 
 int RSPEC_BW_SHIFT ; 
 int RSPEC_MIMORATE ; 
 int TXC_AMPDU_FBR ; 
 int TXC_AMPDU_FIRST ; 
 int TXC_AMPDU_LAST ; 
 int TXC_AMPDU_MASK ; 
 int TXC_AMPDU_SHIFT ; 
 int TXC_PREAMBLE_RTS_FB_SHORT ; 
 int TXC_PREAMBLE_RTS_MAIN_SHORT ; 
 int TXC_SENDCTS ; 
 int TXC_SENDRTS ; 
 int TXC_STARTMSDU ; 
 int TXFID_QUEUE_MASK ; 
 int brcms_c_calc_lsig_len (struct brcms_c_info*,int,int) ; 
 int brcms_c_compute_rtscts_dur (struct brcms_c_info*,int,int,int,int,int,int,int) ; 
 int brcms_c_rspec_to_rts_rspec (struct brcms_c_info*,int,int,int) ; 
 int /*<<< orphan*/  brcms_dbg_ht (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cck_phy2mac_rate (int) ; 
 int cck_rspec (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 scalar_t__ ieee80211_is_cts (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_rts (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 scalar_t__ mcs_2_rate (int,int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ plcp3_issgi (int) ; 
 size_t roundup (size_t,int) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek_tail (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlc_phy_chanspec_get (int /*<<< orphan*/ ) ; 

void brcms_c_ampdu_finalize(struct brcms_ampdu_session *session)
{
	struct brcms_c_info *wlc = session->wlc;
	struct ampdu_info *ampdu = wlc->ampdu;
	struct sk_buff *first, *last;
	struct d11txh *txh;
	struct ieee80211_tx_info *tx_info;
	struct ieee80211_tx_rate *txrate;
	u8 ndelim;
	u8 *plcp;
	uint len;
	uint fifo;
	struct brcms_fifo_info *f;
	u16 mcl;
	bool fbr;
	bool fbr_iscck;
	struct ieee80211_rts *rts;
	bool use_rts = false, use_cts = false;
	u16 dma_len = session->dma_len;
	u16 mimo_ctlchbw = PHY_TXC1_BW_20MHZ;
	u32 rspec = 0, rspec_fallback = 0;
	u32 rts_rspec = 0, rts_rspec_fallback = 0;
	u8 plcp0, plcp3, is40, sgi, mcs;
	u16 mch;
	u8 preamble_type = BRCMS_GF_PREAMBLE;
	u8 fbr_preamble_type = BRCMS_GF_PREAMBLE;
	u8 rts_preamble_type = BRCMS_LONG_PREAMBLE;
	u8 rts_fbr_preamble_type = BRCMS_LONG_PREAMBLE;

	if (skb_queue_empty(&session->skb_list))
		return;

	first = skb_peek(&session->skb_list);
	last = skb_peek_tail(&session->skb_list);

	/* Need to fix up last MPDU first to adjust AMPDU length */
	txh = (struct d11txh *)last->data;
	fifo = le16_to_cpu(txh->TxFrameID) & TXFID_QUEUE_MASK;
	f = &ampdu->fifo_tb[fifo];

	mcl = le16_to_cpu(txh->MacTxControlLow);
	mcl &= ~TXC_AMPDU_MASK;
	mcl |= (TXC_AMPDU_LAST << TXC_AMPDU_SHIFT);
	txh->MacTxControlLow = cpu_to_le16(mcl);

	/* remove the null delimiter after last mpdu */
	ndelim = txh->RTSPLCPFallback[AMPDU_FBR_NULL_DELIM];
	txh->RTSPLCPFallback[AMPDU_FBR_NULL_DELIM] = 0;
	session->ampdu_len -= ndelim * AMPDU_DELIMITER_LEN;

	/* remove the pad len from last mpdu */
	fbr_iscck = ((le16_to_cpu(txh->XtraFrameTypes) & 0x3) == 0);
	len = fbr_iscck ? BRCMS_GET_CCK_PLCP_LEN(txh->FragPLCPFallback) :
			  BRCMS_GET_MIMO_PLCP_LEN(txh->FragPLCPFallback);
	session->ampdu_len -= roundup(len, 4) - len;

	/* Now fix up the first MPDU */
	tx_info = IEEE80211_SKB_CB(first);
	txrate = tx_info->status.rates;
	txh = (struct d11txh *)first->data;
	plcp = (u8 *)(txh + 1);
	rts = (struct ieee80211_rts *)&txh->rts_frame;

	mcl = le16_to_cpu(txh->MacTxControlLow);
	/* If only one MPDU leave it marked as last */
	if (first != last) {
		mcl &= ~TXC_AMPDU_MASK;
		mcl |= (TXC_AMPDU_FIRST << TXC_AMPDU_SHIFT);
	}
	mcl |= TXC_STARTMSDU;
	if (ieee80211_is_rts(rts->frame_control)) {
		mcl |= TXC_SENDRTS;
		use_rts = true;
	}
	if (ieee80211_is_cts(rts->frame_control)) {
		mcl |= TXC_SENDCTS;
		use_cts = true;
	}
	txh->MacTxControlLow = cpu_to_le16(mcl);

	fbr = txrate[1].count > 0;
	if (!fbr) {
		plcp0 = plcp[0];
		plcp3 = plcp[3];
	} else {
		plcp0 = txh->FragPLCPFallback[0];
		plcp3 = txh->FragPLCPFallback[3];
	}
	is40 = (plcp0 & MIMO_PLCP_40MHZ) ? 1 : 0;
	sgi = plcp3_issgi(plcp3) ? 1 : 0;
	mcs = plcp0 & ~MIMO_PLCP_40MHZ;

	if (is40) {
		if (CHSPEC_SB_UPPER(wlc_phy_chanspec_get(wlc->band->pi)))
			mimo_ctlchbw = PHY_TXC1_BW_20MHZ_UP;
		else
			mimo_ctlchbw = PHY_TXC1_BW_20MHZ;
	}

	/* rebuild the rspec and rspec_fallback */
	rspec = RSPEC_MIMORATE;
	rspec |= plcp[0] & ~MIMO_PLCP_40MHZ;
	if (plcp[0] & MIMO_PLCP_40MHZ)
		rspec |= (PHY_TXC1_BW_40MHZ << RSPEC_BW_SHIFT);

	fbr_iscck = !(le16_to_cpu(txh->XtraFrameTypes) & 0x03);
	if (fbr_iscck) {
		rspec_fallback =
			cck_rspec(cck_phy2mac_rate(txh->FragPLCPFallback[0]));
	} else {
		rspec_fallback = RSPEC_MIMORATE;
		rspec_fallback |= txh->FragPLCPFallback[0] & ~MIMO_PLCP_40MHZ;
		if (txh->FragPLCPFallback[0] & MIMO_PLCP_40MHZ)
			rspec_fallback |= PHY_TXC1_BW_40MHZ << RSPEC_BW_SHIFT;
	}

	if (use_rts || use_cts) {
		rts_rspec =
			brcms_c_rspec_to_rts_rspec(wlc, rspec,
						   false, mimo_ctlchbw);
		rts_rspec_fallback =
			brcms_c_rspec_to_rts_rspec(wlc, rspec_fallback,
						   false, mimo_ctlchbw);
	}

	BRCMS_SET_MIMO_PLCP_LEN(plcp, session->ampdu_len);
	/* mark plcp to indicate ampdu */
	BRCMS_SET_MIMO_PLCP_AMPDU(plcp);

	/* reset the mixed mode header durations */
	if (txh->MModeLen) {
		u16 mmodelen = brcms_c_calc_lsig_len(wlc, rspec,
						     session->ampdu_len);
		txh->MModeLen = cpu_to_le16(mmodelen);
		preamble_type = BRCMS_MM_PREAMBLE;
	}
	if (txh->MModeFbrLen) {
		u16 mmfbrlen = brcms_c_calc_lsig_len(wlc, rspec_fallback,
						     session->ampdu_len);
		txh->MModeFbrLen = cpu_to_le16(mmfbrlen);
		fbr_preamble_type = BRCMS_MM_PREAMBLE;
	}

	/* set the preload length */
	if (mcs_2_rate(mcs, true, false) >= f->dmaxferrate) {
		dma_len = min(dma_len, f->ampdu_pld_size);
		txh->PreloadSize = cpu_to_le16(dma_len);
	} else {
		txh->PreloadSize = 0;
	}

	mch = le16_to_cpu(txh->MacTxControlHigh);

	/* update RTS dur fields */
	if (use_rts || use_cts) {
		u16 durid;
		if ((mch & TXC_PREAMBLE_RTS_MAIN_SHORT) ==
		    TXC_PREAMBLE_RTS_MAIN_SHORT)
			rts_preamble_type = BRCMS_SHORT_PREAMBLE;

		if ((mch & TXC_PREAMBLE_RTS_FB_SHORT) ==
		     TXC_PREAMBLE_RTS_FB_SHORT)
			rts_fbr_preamble_type = BRCMS_SHORT_PREAMBLE;

		durid = brcms_c_compute_rtscts_dur(wlc, use_cts, rts_rspec,
						   rspec, rts_preamble_type,
						   preamble_type,
						   session->ampdu_len, true);
		rts->duration = cpu_to_le16(durid);
		durid = brcms_c_compute_rtscts_dur(wlc, use_cts,
						   rts_rspec_fallback,
						   rspec_fallback,
						   rts_fbr_preamble_type,
						   fbr_preamble_type,
						   session->ampdu_len, true);
		txh->RTSDurFallback = cpu_to_le16(durid);
		/* set TxFesTimeNormal */
		txh->TxFesTimeNormal = rts->duration;
		/* set fallback rate version of TxFesTimeNormal */
		txh->TxFesTimeFallback = txh->RTSDurFallback;
	}

	/* set flag and plcp for fallback rate */
	if (fbr) {
		mch |= TXC_AMPDU_FBR;
		txh->MacTxControlHigh = cpu_to_le16(mch);
		BRCMS_SET_MIMO_PLCP_AMPDU(plcp);
		BRCMS_SET_MIMO_PLCP_AMPDU(txh->FragPLCPFallback);
	}

	brcms_dbg_ht(wlc->hw->d11core, "wl%d: count %d ampdu_len %d\n",
		     wlc->pub->unit, skb_queue_len(&session->skb_list),
		     session->ampdu_len);
}