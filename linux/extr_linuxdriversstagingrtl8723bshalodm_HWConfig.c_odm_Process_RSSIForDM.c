#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct odm_phy_info {scalar_t__* rx_mimo_signal_strength; int rx_pwd_ba11; } ;
struct odm_packet_info {int station_id; scalar_t__ data_rate; scalar_t__ is_beacon; scalar_t__ to_self; int /*<<< orphan*/  bssid_match; } ;
typedef  int s32 ;
struct TYPE_7__ {int /*<<< orphan*/  NumQryBeaconPkt; } ;
struct TYPE_10__ {scalar_t__ RxRate; int SupportAbility; int RSSI_A; int RSSI_B; TYPE_1__ PhyDbgInfo; TYPE_3__** pODM_StaInfo; } ;
struct TYPE_8__ {int UndecoratedSmoothedCCK; int UndecoratedSmoothedOFDM; int UndecoratedSmoothedPWDB; int PacketMap; int ValidBit; } ;
struct TYPE_9__ {TYPE_2__ rssi_stat; } ;
typedef  TYPE_3__* PSTA_INFO_T ;
typedef  TYPE_4__* PDM_ODM_T ;

/* Variables and functions */
 int BIT0 ; 
 scalar_t__ DESC_RATE11M ; 
 int /*<<< orphan*/  IS_STA_VALID (TYPE_3__*) ; 
 int ODM_BB_ANT_DIV ; 
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 
 int Rx_Smooth_Factor ; 

__attribute__((used)) static void odm_Process_RSSIForDM(
	PDM_ODM_T pDM_Odm, struct odm_phy_info *pPhyInfo, struct odm_packet_info *pPktinfo
)
{

	s32 UndecoratedSmoothedPWDB, UndecoratedSmoothedCCK, UndecoratedSmoothedOFDM, RSSI_Ave;
	u8 isCCKrate = 0;
	u8 RSSI_max, RSSI_min, i;
	u32 OFDM_pkt = 0;
	u32 Weighting = 0;
	PSTA_INFO_T pEntry;


	if (pPktinfo->station_id == 0xFF)
		return;

	pEntry = pDM_Odm->pODM_StaInfo[pPktinfo->station_id];

	if (!IS_STA_VALID(pEntry))
		return;

	if ((!pPktinfo->bssid_match))
		return;

	if (pPktinfo->is_beacon)
		pDM_Odm->PhyDbgInfo.NumQryBeaconPkt++;

	isCCKrate = ((pPktinfo->data_rate <= DESC_RATE11M)) ? true : false;
	pDM_Odm->RxRate = pPktinfo->data_rate;

	/* Statistic for antenna/path diversity------------------ */
	if (pDM_Odm->SupportAbility & ODM_BB_ANT_DIV) {

	}

	/* Smart Antenna Debug Message------------------ */

	UndecoratedSmoothedCCK = pEntry->rssi_stat.UndecoratedSmoothedCCK;
	UndecoratedSmoothedOFDM = pEntry->rssi_stat.UndecoratedSmoothedOFDM;
	UndecoratedSmoothedPWDB = pEntry->rssi_stat.UndecoratedSmoothedPWDB;

	if (pPktinfo->to_self || pPktinfo->is_beacon) {

		if (!isCCKrate) { /* ofdm rate */
			if (pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_B] == 0) {
				RSSI_Ave = pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_A];
				pDM_Odm->RSSI_A = pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_A];
				pDM_Odm->RSSI_B = 0;
			} else {
				/* DbgPrint("pRfd->Status.rx_mimo_signal_strength[0] = %d, pRfd->Status.rx_mimo_signal_strength[1] = %d\n", */
					/* pRfd->Status.rx_mimo_signal_strength[0], pRfd->Status.rx_mimo_signal_strength[1]); */
				pDM_Odm->RSSI_A =  pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_A];
				pDM_Odm->RSSI_B = pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_B];

				if (
					pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_A] >
					pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_B]
				) {
					RSSI_max = pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_A];
					RSSI_min = pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_B];
				} else {
					RSSI_max = pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_B];
					RSSI_min = pPhyInfo->rx_mimo_signal_strength[ODM_RF_PATH_A];
				}

				if ((RSSI_max-RSSI_min) < 3)
					RSSI_Ave = RSSI_max;
				else if ((RSSI_max-RSSI_min) < 6)
					RSSI_Ave = RSSI_max - 1;
				else if ((RSSI_max-RSSI_min) < 10)
					RSSI_Ave = RSSI_max - 2;
				else
					RSSI_Ave = RSSI_max - 3;
			}

			/* 1 Process OFDM RSSI */
			if (UndecoratedSmoothedOFDM <= 0)	/*  initialize */
				UndecoratedSmoothedOFDM = pPhyInfo->rx_pwd_ba11;
			else {
				if (pPhyInfo->rx_pwd_ba11 > (u32)UndecoratedSmoothedOFDM) {
					UndecoratedSmoothedOFDM =
							((UndecoratedSmoothedOFDM*(Rx_Smooth_Factor-1)) +
							RSSI_Ave)/Rx_Smooth_Factor;
					UndecoratedSmoothedOFDM = UndecoratedSmoothedOFDM + 1;
				} else {
					UndecoratedSmoothedOFDM =
							((UndecoratedSmoothedOFDM*(Rx_Smooth_Factor-1)) +
							RSSI_Ave)/Rx_Smooth_Factor;
				}
			}

			pEntry->rssi_stat.PacketMap = (pEntry->rssi_stat.PacketMap<<1) | BIT0;

		} else {
			RSSI_Ave = pPhyInfo->rx_pwd_ba11;
			pDM_Odm->RSSI_A = (u8) pPhyInfo->rx_pwd_ba11;
			pDM_Odm->RSSI_B = 0;

			/* 1 Process CCK RSSI */
			if (UndecoratedSmoothedCCK <= 0)	/*  initialize */
				UndecoratedSmoothedCCK = pPhyInfo->rx_pwd_ba11;
			else {
				if (pPhyInfo->rx_pwd_ba11 > (u32)UndecoratedSmoothedCCK) {
					UndecoratedSmoothedCCK =
							((UndecoratedSmoothedCCK*(Rx_Smooth_Factor-1)) +
							pPhyInfo->rx_pwd_ba11)/Rx_Smooth_Factor;
					UndecoratedSmoothedCCK = UndecoratedSmoothedCCK + 1;
				} else {
					UndecoratedSmoothedCCK =
							((UndecoratedSmoothedCCK*(Rx_Smooth_Factor-1)) +
							pPhyInfo->rx_pwd_ba11)/Rx_Smooth_Factor;
				}
			}
			pEntry->rssi_stat.PacketMap = pEntry->rssi_stat.PacketMap<<1;
		}

		/* if (pEntry) */
		{
			/* 2011.07.28 LukeLee: modified to prevent unstable CCK RSSI */
			if (pEntry->rssi_stat.ValidBit >= 64)
				pEntry->rssi_stat.ValidBit = 64;
			else
				pEntry->rssi_stat.ValidBit++;

			for (i = 0; i < pEntry->rssi_stat.ValidBit; i++)
				OFDM_pkt += (u8)(pEntry->rssi_stat.PacketMap>>i)&BIT0;

			if (pEntry->rssi_stat.ValidBit == 64) {
				Weighting = ((OFDM_pkt<<4) > 64)?64:(OFDM_pkt<<4);
				UndecoratedSmoothedPWDB = (Weighting*UndecoratedSmoothedOFDM+(64-Weighting)*UndecoratedSmoothedCCK)>>6;
			} else {
				if (pEntry->rssi_stat.ValidBit != 0)
					UndecoratedSmoothedPWDB = (OFDM_pkt*UndecoratedSmoothedOFDM+(pEntry->rssi_stat.ValidBit-OFDM_pkt)*UndecoratedSmoothedCCK)/pEntry->rssi_stat.ValidBit;
				else
					UndecoratedSmoothedPWDB = 0;
			}

			pEntry->rssi_stat.UndecoratedSmoothedCCK = UndecoratedSmoothedCCK;
			pEntry->rssi_stat.UndecoratedSmoothedOFDM = UndecoratedSmoothedOFDM;
			pEntry->rssi_stat.UndecoratedSmoothedPWDB = UndecoratedSmoothedPWDB;

			/* DbgPrint("OFDM_pkt =%d, Weighting =%d\n", OFDM_pkt, Weighting); */
			/* DbgPrint("UndecoratedSmoothedOFDM =%d, UndecoratedSmoothedPWDB =%d, UndecoratedSmoothedCCK =%d\n", */
			/* UndecoratedSmoothedOFDM, UndecoratedSmoothedPWDB, UndecoratedSmoothedCCK); */

		}

	}
}