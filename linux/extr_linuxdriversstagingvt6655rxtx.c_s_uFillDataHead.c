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
typedef  int u16 ;
struct vnt_tx_datahead_g_fb {void* duration_a; void* time_stamp_off_b; void* time_stamp_off_a; void* duration_a_f1; void* duration_a_f0; void* duration_b; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct vnt_tx_datahead_g {void* duration_a; void* time_stamp_off_b; void* time_stamp_off_a; void* duration_b; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct vnt_tx_datahead_ab {void* duration; void* time_stamp_off; int /*<<< orphan*/  ab; } ;
struct vnt_tx_datahead_a_fb {void* duration; void* time_stamp_off; void* duration_f1; void* duration_f0; int /*<<< orphan*/  a; } ;
struct vnt_private {unsigned short byTopCCKBasicRate; int current_aid; } ;
typedef  void* __le16 ;

/* Variables and functions */
 unsigned char AUTO_FB_NONE ; 
 int BIT (int) ; 
 int /*<<< orphan*/  DATADUR_A ; 
 int /*<<< orphan*/  DATADUR_A_F0 ; 
 int /*<<< orphan*/  DATADUR_A_F1 ; 
 int /*<<< orphan*/  DATADUR_B ; 
 unsigned char PK_TYPE_11A ; 
 unsigned char PK_TYPE_11B ; 
 unsigned char PK_TYPE_11GA ; 
 unsigned char PK_TYPE_11GB ; 
 void* cpu_to_le16 (int) ; 
 scalar_t__ s_uGetDataDuration (struct vnt_private*,int /*<<< orphan*/ ,unsigned int,unsigned char,unsigned short,int,unsigned int,unsigned int,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  vnt_get_phy_field (struct vnt_private*,unsigned int,unsigned short,unsigned char,int /*<<< orphan*/ *) ; 
 void* vnt_time_stamp_off (struct vnt_private*,unsigned short) ; 

__attribute__((used)) static
__le16
s_uFillDataHead(
	struct vnt_private *pDevice,
	unsigned char byPktType,
	void *pTxDataHead,
	unsigned int cbFrameLength,
	unsigned int uDMAIdx,
	bool bNeedAck,
	unsigned int uFragIdx,
	unsigned int cbLastFragmentSize,
	unsigned int uMACfragNum,
	unsigned char byFBOption,
	unsigned short wCurrentRate,
	bool is_pspoll
)
{
	if (!pTxDataHead)
		return 0;

	if (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) {
		if (byFBOption == AUTO_FB_NONE) {
			struct vnt_tx_datahead_g *buf = pTxDataHead;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
					  byPktType, &buf->a);

			vnt_get_phy_field(pDevice, cbFrameLength,
					  pDevice->byTopCCKBasicRate,
					  PK_TYPE_11B, &buf->b);

			if (is_pspoll) {
				__le16 dur = cpu_to_le16(pDevice->current_aid | BIT(14) | BIT(15));

				buf->duration_a = dur;
				buf->duration_b = dur;
			} else {
				/* Get Duration and TimeStamp */
				buf->duration_a =
					cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A, cbFrameLength,
									    byPktType, wCurrentRate, bNeedAck, uFragIdx,
									    cbLastFragmentSize, uMACfragNum,
									    byFBOption));
				buf->duration_b =
					cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_B, cbFrameLength,
									    PK_TYPE_11B, pDevice->byTopCCKBasicRate,
									    bNeedAck, uFragIdx, cbLastFragmentSize,
									    uMACfragNum, byFBOption));
			}

			buf->time_stamp_off_a = vnt_time_stamp_off(pDevice, wCurrentRate);
			buf->time_stamp_off_b = vnt_time_stamp_off(pDevice, pDevice->byTopCCKBasicRate);

			return buf->duration_a;
		} else {
			/* Auto Fallback */
			struct vnt_tx_datahead_g_fb *buf = pTxDataHead;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
					  byPktType, &buf->a);

			vnt_get_phy_field(pDevice, cbFrameLength,
					  pDevice->byTopCCKBasicRate,
					  PK_TYPE_11B, &buf->b);
			/* Get Duration and TimeStamp */
			buf->duration_a = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A, cbFrameLength, byPktType,
									      wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
			buf->duration_b = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_B, cbFrameLength, PK_TYPE_11B,
									       pDevice->byTopCCKBasicRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
			buf->duration_a_f0 = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A_F0, cbFrameLength, byPktType,
										  wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
			buf->duration_a_f1 = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A_F1, cbFrameLength, byPktType,
										 wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));

			buf->time_stamp_off_a = vnt_time_stamp_off(pDevice, wCurrentRate);
			buf->time_stamp_off_b = vnt_time_stamp_off(pDevice, pDevice->byTopCCKBasicRate);

			return buf->duration_a;
		} /* if (byFBOption == AUTO_FB_NONE) */
	} else if (byPktType == PK_TYPE_11A) {
		if (byFBOption != AUTO_FB_NONE) {
			/* Auto Fallback */
			struct vnt_tx_datahead_a_fb *buf = pTxDataHead;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
					  byPktType, &buf->a);

			/* Get Duration and TimeStampOff */
			buf->duration = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A, cbFrameLength, byPktType,
									    wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
			buf->duration_f0 = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A_F0, cbFrameLength, byPktType,
									       wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
			buf->duration_f1 = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A_F1, cbFrameLength, byPktType,
										wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
			buf->time_stamp_off = vnt_time_stamp_off(pDevice, wCurrentRate);
			return buf->duration;
		} else {
			struct vnt_tx_datahead_ab *buf = pTxDataHead;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
					  byPktType, &buf->ab);

			if (is_pspoll) {
				__le16 dur = cpu_to_le16(pDevice->current_aid | BIT(14) | BIT(15));

				buf->duration = dur;
			} else {
				/* Get Duration and TimeStampOff */
				buf->duration =
					cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A, cbFrameLength, byPktType,
									    wCurrentRate, bNeedAck, uFragIdx,
									    cbLastFragmentSize, uMACfragNum,
									    byFBOption));
			}

			buf->time_stamp_off = vnt_time_stamp_off(pDevice, wCurrentRate);
			return buf->duration;
		}
	} else {
		struct vnt_tx_datahead_ab *buf = pTxDataHead;
		/* Get SignalField, ServiceField & Length */
		vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
				  byPktType, &buf->ab);

		if (is_pspoll) {
			__le16 dur = cpu_to_le16(pDevice->current_aid | BIT(14) | BIT(15));

			buf->duration = dur;
		} else {
			/* Get Duration and TimeStampOff */
			buf->duration =
				cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_B, cbFrameLength, byPktType,
								    wCurrentRate, bNeedAck, uFragIdx,
								    cbLastFragmentSize, uMACfragNum,
								    byFBOption));
		}

		buf->time_stamp_off = vnt_time_stamp_off(pDevice, wCurrentRate);
		return buf->duration;
	}
	return 0;
}