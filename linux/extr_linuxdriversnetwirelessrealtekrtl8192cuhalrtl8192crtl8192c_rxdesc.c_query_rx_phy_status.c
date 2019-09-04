#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int mcs_rate; int RxPWDBAll; int RecvSignalPower; int signal_qual; int* rx_mimo_signal_qual; int* rx_rssi; int* rx_snr; int signal_strength; scalar_t__ rxht; } ;
struct TYPE_13__ {struct rx_pkt_attrib attrib; TYPE_5__* adapter; } ;
struct TYPE_14__ {TYPE_2__ hdr; } ;
union recv_frame {TYPE_3__ u; } ;
typedef  int u8 ;
typedef  int u32 ;
struct phy_stat {int dummy; } ;
struct dm_priv {int /*<<< orphan*/  OFDM_Pkt_Cnt; } ;
typedef  int s8 ;
struct TYPE_12__ {int rxpwdb; int* RxRssi; int* RxSNRdB; } ;
struct TYPE_15__ {scalar_t__ rf_pwrstate; } ;
struct TYPE_16__ {TYPE_1__ recvpriv; TYPE_4__ pwrctrlpriv; } ;
typedef  TYPE_5__ _adapter ;
struct TYPE_19__ {scalar_t__ CustomerID; int NumTotalRFPath; scalar_t__* bRFPathRxEnable; scalar_t__ bCckHighPower; struct dm_priv dmpriv; } ;
struct TYPE_18__ {int cck_agc_rpt; int SQ_rpt; } ;
struct TYPE_17__ {int* trsw_gain_X; int* rxsnr_X; int pwdb_all; int /*<<< orphan*/ * rxevm_X; } ;
typedef  TYPE_6__ PHY_STS_OFDM_8192CD_T ;
typedef  TYPE_7__ PHY_STS_CCK_8192CD_T ;
typedef  TYPE_8__ HAL_DATA_TYPE ;

/* Variables and functions */
 TYPE_8__* GET_HAL_DATA (TYPE_5__*) ; 
 scalar_t__ RT_CID_819x_Lenovo ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FALSE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int evm_db2percentage (int /*<<< orphan*/ ) ; 
 int query_rx_pwr_percentage (int) ; 
 scalar_t__ rf_on ; 
 scalar_t__ signal_scale_mapping (TYPE_5__*,int) ; 

__attribute__((used)) static void query_rx_phy_status(union recv_frame *prframe, struct phy_stat *pphy_stat)
{
	PHY_STS_OFDM_8192CD_T	*pOfdm_buf;
	PHY_STS_CCK_8192CD_T	*pCck_buf;
	u8	i, max_spatial_stream, evm;
	s8	rx_pwr[4], rx_pwr_all = 0;
	u8	pwdb_all;
	u32	rssi,total_rssi=0;
	u8 	bcck_rate=0, rf_rx_num = 0, cck_highpwr = 0;
	_adapter				*padapter = prframe->u.hdr.adapter;
	struct rx_pkt_attrib	*pattrib = &prframe->u.hdr.attrib;
	HAL_DATA_TYPE		*pHalData = GET_HAL_DATA(padapter);
	struct dm_priv		*pdmpriv = &pHalData->dmpriv;
	u8	tmp_rxsnr;
	s8	rx_snrX;

#ifdef CONFIG_HW_ANTENNA_DIVERSITY
	PHY_RX_DRIVER_INFO_8192CD *pDrvInfo = ((PHY_RX_DRIVER_INFO_8192CD *)pphy_stat);
	u8 	bant1_sel = (pDrvInfo->ANTSEL == 1)?_TRUE:_FALSE;	
#endif

	// Record it for next packet processing
	bcck_rate=(pattrib->mcs_rate<=3? 1:0);

	if(bcck_rate) //CCK
	{
		u8 report;
#ifdef CONFIG_HW_ANTENNA_DIVERSITY		
		if(bant1_sel == _TRUE)
			pHalData->CCK_Ant1_Cnt++;
		else
			pHalData->CCK_Ant2_Cnt++;
#endif		

		// CCK Driver info Structure is not the same as OFDM packet.
		pCck_buf = (PHY_STS_CCK_8192CD_T *)pphy_stat;
		//Adapter->RxStats.NumQryPhyStatusCCK++;

		//
		// (1)Hardware does not provide RSSI for CCK
		// (2)PWDB, Average PWDB cacluated by hardware (for rate adaptive)
		//

		if(padapter->pwrctrlpriv.rf_pwrstate == rf_on)
			cck_highpwr = (u8)pHalData->bCckHighPower;
		else
			cck_highpwr = _FALSE;

		if(!cck_highpwr)
		{
			report = pCck_buf->cck_agc_rpt&0xc0;
			report = report>>6;
			switch(report)
			{
				// 03312009 modified by cosa
				// Modify the RF RNA gain value to -40, -20, -2, 14 by Jenyu's suggestion
				// Note: different RF with the different RNA gain.
				case 0x3:
					rx_pwr_all = (-46) - (pCck_buf->cck_agc_rpt & 0x3e);
					break;
				case 0x2:
					rx_pwr_all = (-26) - (pCck_buf->cck_agc_rpt & 0x3e);
					break;
				case 0x1:
					rx_pwr_all = (-12) - (pCck_buf->cck_agc_rpt & 0x3e);
					break;
				case 0x0:
					rx_pwr_all = (16) - (pCck_buf->cck_agc_rpt & 0x3e);
					break;
			}
		}
		else
		{
			report = pCck_buf->cck_agc_rpt & 0x60;
			report = report>>5;
			switch(report)
			{
				case 0x3:
					rx_pwr_all = (-46) - ((pCck_buf->cck_agc_rpt & 0x1f)<<1) ;
					break;
				case 0x2:
					rx_pwr_all = (-26)- ((pCck_buf->cck_agc_rpt & 0x1f)<<1);
					break;
				case 0x1:
					rx_pwr_all = (-12) - ((pCck_buf->cck_agc_rpt & 0x1f)<<1) ;
					break;
				case 0x0:
					rx_pwr_all = (16) - ((pCck_buf->cck_agc_rpt & 0x1f)<<1) ;
					break;
			}
		}

		pwdb_all= query_rx_pwr_percentage(rx_pwr_all);
		if(pHalData->CustomerID == RT_CID_819x_Lenovo)
		{
			// CCK gain is smaller than OFDM/MCS gain,
			// so we add gain diff by experiences, the val is 6
			pwdb_all+=6;
			if(pwdb_all > 100)
				pwdb_all = 100;
			// modify the offset to make the same gain index with OFDM.
			if(pwdb_all > 34 && pwdb_all <= 42)
				pwdb_all -= 2;
			else if(pwdb_all > 26 && pwdb_all <= 34)
				pwdb_all -= 6;
			else if(pwdb_all > 14 && pwdb_all <= 26)
				pwdb_all -= 8;
			else if(pwdb_all > 4 && pwdb_all <= 14)
				pwdb_all -= 4;
		}

		pattrib->RxPWDBAll = pwdb_all;	//for DIG/rate adaptive
		pattrib->RecvSignalPower = rx_pwr_all;	//dBM
		padapter->recvpriv.rxpwdb = rx_pwr_all;
		//
		// (3) Get Signal Quality (EVM)
		//
		//if(bPacketMatchBSSID)
		{
			u8	sq;

			if(pHalData->CustomerID == RT_CID_819x_Lenovo)
			{
				// mapping to 5 bars for vista signal strength
				// signal quality in driver will be displayed to signal strength
				// in vista.
				if(pwdb_all >= 50)
					sq = 100;
				else if(pwdb_all >= 35 && pwdb_all < 50)
					sq = 80;
				else if(pwdb_all >= 22 && pwdb_all < 35)
					sq = 60;
				else if(pwdb_all >= 18 && pwdb_all < 22)
					sq = 40;
				else
					sq = 20;
			}
			else
			{
				if(pwdb_all> 40)
				{
					sq = 100;
				}
				else
				{
					sq = pCck_buf->SQ_rpt;

					if(pCck_buf->SQ_rpt > 64)
						sq = 0;
					else if (pCck_buf->SQ_rpt < 20)
						sq= 100;
					else
						sq = ((64-sq) * 100) / 44;

				}
			}

			pattrib->signal_qual=sq;
			pattrib->rx_mimo_signal_qual[0]=sq;
			pattrib->rx_mimo_signal_qual[1]=(-1);
		}

	}
	else //OFDM/HT
	{
#ifdef CONFIG_HW_ANTENNA_DIVERSITY	
		if(bant1_sel == _TRUE)
			pHalData->OFDM_Ant1_Cnt++;
		else
			pHalData->OFDM_Ant2_Cnt++;
#endif
		pdmpriv->OFDM_Pkt_Cnt++;

		pOfdm_buf = (PHY_STS_OFDM_8192CD_T *)pphy_stat;
	
		//
		// (1)Get RSSI per-path
		//
		for(i=0; i<pHalData->NumTotalRFPath; i++)
		{
			// 2008/01/30 MH we will judge RF RX path now.
			if (pHalData->bRFPathRxEnable[i])
				rf_rx_num++;
			//else
				//continue;

			rx_pwr[i] =  ((pOfdm_buf->trsw_gain_X[i]&0x3F)*2) - 110;
			padapter->recvpriv.RxRssi[i] = rx_pwr[i];
			/* Translate DBM to percentage. */
			pattrib->rx_rssi[i] = rssi = query_rx_pwr_percentage(rx_pwr[i]);
			total_rssi += rssi;

			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("RF-%d RXPWR=%x RSSI=%d\n", i, rx_pwr[i], rssi));

			//Get Rx snr value in DB
			tmp_rxsnr =	pOfdm_buf->rxsnr_X[i];
			rx_snrX = (s8)(tmp_rxsnr);
			rx_snrX >>= 1;
			padapter->recvpriv.RxSNRdB[i] =  (int)rx_snrX;
			pattrib->rx_snr[i]=pOfdm_buf->rxsnr_X[i];
			/* Record Signal Strength for next packet */
			//if(bPacketMatchBSSID)
			{
				//pRfd->Status.RxMIMOSignalStrength[i] =(u1Byte) RSSI;

				//The following is for lenovo signal strength in vista
				if(pHalData->CustomerID == RT_CID_819x_Lenovo)
				{
					u8	sq;

					if(i == 0)
					{
						// mapping to 5 bars for vista signal strength
						// signal quality in driver will be displayed to signal strength
						// in vista.
						if(rssi >= 50)
							sq = 100;
						else if(rssi >= 35 && rssi < 50)
							sq = 80;
						else if(rssi >= 22 && rssi < 35)
							sq = 60;
						else if(rssi >= 18 && rssi < 22)
							sq = 40;
						else
							sq = 20;
						//DbgPrint("ofdm/mcs RSSI=%d\n", RSSI);
						//pRfd->Status.SignalQuality = SQ;
						//DbgPrint("ofdm/mcs SQ = %d\n", pRfd->Status.SignalQuality);
					}
				}
			}
		}


		//
		// (2)PWDB, Average PWDB cacluated by hardware (for rate adaptive),average
		//
		rx_pwr_all = (((pOfdm_buf->pwdb_all ) >> 1 )& 0x7f) -110;//for OFDM Average RSSI
		pwdb_all = query_rx_pwr_percentage(rx_pwr_all);

		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("PWDB_ALL=%d\n",	pwdb_all));

		pattrib->RxPWDBAll = pwdb_all;	//for DIG/rate adaptive
		pattrib->RecvSignalPower = rx_pwr_all;//dBM
		padapter->recvpriv.rxpwdb = rx_pwr_all;
		//
		// (3)EVM of HT rate
		//
		if(pHalData->CustomerID != RT_CID_819x_Lenovo)
		{
			if(pattrib->rxht &&  pattrib->mcs_rate >=20 && pattrib->mcs_rate<=27)
				max_spatial_stream = 2; //both spatial stream make sense
			else
				max_spatial_stream = 1; //only spatial stream 1 makes sense

			for(i=0; i<max_spatial_stream; i++)
			{
				// Do not use shift operation like "rx_evmX >>= 1" because the compilor of free build environment
				// fill most significant bit to "zero" when doing shifting operation which may change a negative
				// value to positive one, then the dbm value (which is supposed to be negative)  is not correct anymore.
				evm = evm_db2percentage( (pOfdm_buf->rxevm_X[i]/*/ 2*/));//dbm

				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("RXRATE=%x RXEVM=%x EVM=%s%d\n",
					pattrib->mcs_rate, pOfdm_buf->rxevm_X[i], "%",evm));

				//if(bPacketMatchBSSID)
				{
					if(i==0) // Fill value in RFD, Get the first spatial stream only
					{
						pattrib->signal_qual = (u8)(evm & 0xff);
					}
					pattrib->rx_mimo_signal_qual[i] = (u8)(evm & 0xff);
				}
			}

		}

		//
		// 4. Record rx statistics for debug
		//

	}


	//UI BSS List signal strength(in percentage), make it good looking, from 0~100.
	//It is assigned to the BSS List in GetValueFromBeaconOrProbeRsp().
	if(bcck_rate)
	{
		pattrib->signal_strength=(u8)signal_scale_mapping(padapter, pwdb_all);
	}
	else
	{
		if (rf_rx_num != 0)
		{
			pattrib->signal_strength= (u8)(signal_scale_mapping(padapter, total_rssi/=rf_rx_num));
		}
	}
	//DBG_8192C("%s,rx_pwr_all(%d),RxPWDBAll(%d)\n",__FUNCTION__,rx_pwr_all,pattrib->RxPWDBAll);

}