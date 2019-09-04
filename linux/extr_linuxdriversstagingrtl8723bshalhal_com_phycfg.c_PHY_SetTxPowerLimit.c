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
typedef  size_t u8 ;
struct hal_com_data {scalar_t__***** TxPwrLimit_2_4G; scalar_t__***** TxPwrLimit_5G; } ;
struct adapter {int dummy; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  BAND_ON_5G ; 
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  GetU1ByteIntegerFromStringInDecimal (scalar_t__*,...) ; 
 scalar_t__ MAX_POWER_INDEX ; 
 size_t ODM_RF_PATH_A ; 
 scalar_t__ eqNByte (size_t*,size_t*,int) ; 
 scalar_t__ phy_GetChannelIndexOfTxPowerLimit (int /*<<< orphan*/ ,size_t) ; 

void PHY_SetTxPowerLimit(
	struct adapter *Adapter,
	u8 *Regulation,
	u8 *Band,
	u8 *Bandwidth,
	u8 *RateSection,
	u8 *RfPath,
	u8 *Channel,
	u8 *PowerLimit
)
{
	struct hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	u8 regulation = 0, bandwidth = 0, rateSection = 0, channel;
	s8 powerLimit = 0, prevPowerLimit, channelIndex;

	/* DBG_871X("Index of power limit table [band %s][regulation %s][bw %s][rate section %s][rf path %s][chnl %s][val %s]\n", */
	/*	  Band, Regulation, Bandwidth, RateSection, RfPath, Channel, PowerLimit); */

	if (!GetU1ByteIntegerFromStringInDecimal((s8 *)Channel, &channel) ||
		 !GetU1ByteIntegerFromStringInDecimal((s8 *)PowerLimit, &powerLimit))
		DBG_871X("Illegal index of power limit table [chnl %s][val %s]\n", Channel, PowerLimit);

	powerLimit = powerLimit > MAX_POWER_INDEX ? MAX_POWER_INDEX : powerLimit;

	if (eqNByte(Regulation, (u8 *)("FCC"), 3))
		regulation = 0;
	else if (eqNByte(Regulation, (u8 *)("MKK"), 3))
		regulation = 1;
	else if (eqNByte(Regulation, (u8 *)("ETSI"), 4))
		regulation = 2;
	else if (eqNByte(Regulation, (u8 *)("WW13"), 4))
		regulation = 3;

	if (eqNByte(RateSection, (u8 *)("CCK"), 3) && eqNByte(RfPath, (u8 *)("1T"), 2))
		rateSection = 0;
	else if (eqNByte(RateSection, (u8 *)("OFDM"), 4) && eqNByte(RfPath, (u8 *)("1T"), 2))
		rateSection = 1;
	else if (eqNByte(RateSection, (u8 *)("HT"), 2) && eqNByte(RfPath, (u8 *)("1T"), 2))
		rateSection = 2;
	else if (eqNByte(RateSection, (u8 *)("HT"), 2) && eqNByte(RfPath, (u8 *)("2T"), 2))
		rateSection = 3;
	else if (eqNByte(RateSection, (u8 *)("HT"), 2) && eqNByte(RfPath, (u8 *)("3T"), 2))
		rateSection = 4;
	else if (eqNByte(RateSection, (u8 *)("HT"), 2) && eqNByte(RfPath, (u8 *)("4T"), 2))
		rateSection = 5;
	else if (eqNByte(RateSection, (u8 *)("VHT"), 3) && eqNByte(RfPath, (u8 *)("1T"), 2))
		rateSection = 6;
	else if (eqNByte(RateSection, (u8 *)("VHT"), 3) && eqNByte(RfPath, (u8 *)("2T"), 2))
		rateSection = 7;
	else if (eqNByte(RateSection, (u8 *)("VHT"), 3) && eqNByte(RfPath, (u8 *)("3T"), 2))
		rateSection = 8;
	else if (eqNByte(RateSection, (u8 *)("VHT"), 3) && eqNByte(RfPath, (u8 *)("4T"), 2))
		rateSection = 9;
	else {
		DBG_871X("Wrong rate section!\n");
		return;
	}


	if (eqNByte(Bandwidth, (u8 *)("20M"), 3))
		bandwidth = 0;
	else if (eqNByte(Bandwidth, (u8 *)("40M"), 3))
		bandwidth = 1;
	else if (eqNByte(Bandwidth, (u8 *)("80M"), 3))
		bandwidth = 2;
	else if (eqNByte(Bandwidth, (u8 *)("160M"), 4))
		bandwidth = 3;

	if (eqNByte(Band, (u8 *)("2.4G"), 4)) {
		channelIndex = phy_GetChannelIndexOfTxPowerLimit(BAND_ON_2_4G, channel);

		if (channelIndex == -1)
			return;

		prevPowerLimit = pHalData->TxPwrLimit_2_4G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A];

		if (powerLimit < prevPowerLimit)
			pHalData->TxPwrLimit_2_4G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A] = powerLimit;

		/* DBG_871X("2.4G Band value : [regulation %d][bw %d][rate_section %d][chnl %d][val %d]\n", */
		/*	  regulation, bandwidth, rateSection, channelIndex, pHalData->TxPwrLimit_2_4G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A]); */
	} else if (eqNByte(Band, (u8 *)("5G"), 2)) {
		channelIndex = phy_GetChannelIndexOfTxPowerLimit(BAND_ON_5G, channel);

		if (channelIndex == -1)
			return;

		prevPowerLimit = pHalData->TxPwrLimit_5G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A];

		if (powerLimit < prevPowerLimit)
			pHalData->TxPwrLimit_5G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A] = powerLimit;

		/* DBG_871X("5G Band value : [regulation %d][bw %d][rate_section %d][chnl %d][val %d]\n", */
		/*	  regulation, bandwidth, rateSection, channel, pHalData->TxPwrLimit_5G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A]); */
	} else {
		DBG_871X("Cannot recognize the band info in %s\n", Band);
		return;
	}
}