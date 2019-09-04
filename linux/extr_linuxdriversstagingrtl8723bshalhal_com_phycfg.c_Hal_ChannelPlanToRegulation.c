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
struct hal_com_data {void* Regulation5G; void* Regulation2_4G; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
#define  RT_CHANNEL_DOMAIN_ETSI1_ETSI4 166 
#define  RT_CHANNEL_DOMAIN_ETSI1_NULL 165 
#define  RT_CHANNEL_DOMAIN_ETSI2_NULL 164 
#define  RT_CHANNEL_DOMAIN_FCC1_FCC1 163 
#define  RT_CHANNEL_DOMAIN_FCC1_FCC10 162 
#define  RT_CHANNEL_DOMAIN_FCC1_FCC2 161 
#define  RT_CHANNEL_DOMAIN_FCC1_FCC7 160 
#define  RT_CHANNEL_DOMAIN_FCC1_FCC8 159 
#define  RT_CHANNEL_DOMAIN_FCC1_FCC9 158 
#define  RT_CHANNEL_DOMAIN_FCC1_NCC1 157 
#define  RT_CHANNEL_DOMAIN_FCC1_NCC2 156 
#define  RT_CHANNEL_DOMAIN_FCC1_NCC3 155 
#define  RT_CHANNEL_DOMAIN_FCC1_NCC4 154 
#define  RT_CHANNEL_DOMAIN_FCC1_NULL 153 
#define  RT_CHANNEL_DOMAIN_GLOBAL_NULL 152 
#define  RT_CHANNEL_DOMAIN_MKK1_MKK1 151 
#define  RT_CHANNEL_DOMAIN_MKK1_MKK2 150 
#define  RT_CHANNEL_DOMAIN_MKK1_MKK3 149 
#define  RT_CHANNEL_DOMAIN_MKK1_NULL 148 
#define  RT_CHANNEL_DOMAIN_REALTEK_DEFINE 147 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI1 146 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI10 145 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI11 144 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI12 143 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI13 142 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI2 141 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI3 140 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI5 139 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI6 138 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI7 137 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI8 136 
#define  RT_CHANNEL_DOMAIN_WORLD_ETSI9 135 
#define  RT_CHANNEL_DOMAIN_WORLD_FCC2 134 
#define  RT_CHANNEL_DOMAIN_WORLD_FCC3 133 
#define  RT_CHANNEL_DOMAIN_WORLD_FCC4 132 
#define  RT_CHANNEL_DOMAIN_WORLD_FCC5 131 
#define  RT_CHANNEL_DOMAIN_WORLD_FCC6 130 
#define  RT_CHANNEL_DOMAIN_WORLD_KCC1 129 
#define  RT_CHANNEL_DOMAIN_WORLD_NULL 128 
 void* TXPWR_LMT_ETSI ; 
 void* TXPWR_LMT_FCC ; 
 void* TXPWR_LMT_MKK ; 
 void* TXPWR_LMT_WW ; 

void Hal_ChannelPlanToRegulation(struct adapter *Adapter, u16 ChannelPlan)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	pHalData->Regulation2_4G = TXPWR_LMT_WW;
	pHalData->Regulation5G = TXPWR_LMT_WW;

	switch (ChannelPlan) {
	case RT_CHANNEL_DOMAIN_WORLD_NULL:
		pHalData->Regulation2_4G = TXPWR_LMT_WW;
		break;
	case RT_CHANNEL_DOMAIN_ETSI1_NULL:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_NULL:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_MKK1_NULL:
		pHalData->Regulation2_4G = TXPWR_LMT_MKK;
		break;
	case RT_CHANNEL_DOMAIN_ETSI2_NULL:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_FCC1:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI1:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_MKK1_MKK1:
		pHalData->Regulation2_4G = TXPWR_LMT_MKK;
		pHalData->Regulation5G = TXPWR_LMT_MKK;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_KCC1:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_MKK;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_FCC2:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_FCC3:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_FCC4:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_FCC5:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_FCC6:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_FCC7:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI2:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI3:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_MKK1_MKK2:
		pHalData->Regulation2_4G = TXPWR_LMT_MKK;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_MKK1_MKK3:
		pHalData->Regulation2_4G = TXPWR_LMT_MKK;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_NCC1:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_NCC2:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_GLOBAL_NULL:
		pHalData->Regulation2_4G = TXPWR_LMT_WW;
		pHalData->Regulation5G = TXPWR_LMT_WW;
		break;
	case RT_CHANNEL_DOMAIN_ETSI1_ETSI4:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_FCC2:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_NCC3:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI5:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_FCC8:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI6:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI7:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI8:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI9:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI10:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI11:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_NCC4:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI12:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_FCC9:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_WORLD_ETSI13:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		break;
	case RT_CHANNEL_DOMAIN_FCC1_FCC10:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		break;
	case RT_CHANNEL_DOMAIN_REALTEK_DEFINE: /* Realtek Reserve */
		pHalData->Regulation2_4G = TXPWR_LMT_WW;
		pHalData->Regulation5G = TXPWR_LMT_WW;
		break;
	default:
		break;
	}
}