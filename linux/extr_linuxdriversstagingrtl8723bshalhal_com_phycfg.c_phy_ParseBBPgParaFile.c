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
typedef  int u32 ;
struct TYPE_4__ {char PhyRegPgVersion; scalar_t__ PhyRegPgValueType; } ;
struct hal_com_data {TYPE_2__ odmpriv; } ;
struct TYPE_3__ {int RegDecryptCustomFile; } ;
struct adapter {TYPE_1__ registrypriv; } ;

/* Variables and functions */
 int BAND_ON_2_4G ; 
 int BAND_ON_5G ; 
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 scalar_t__ GetFractionValueFromString (char*,int*,int*,int*) ; 
 scalar_t__ GetHexValueFromString (char*,int*,int*) ; 
 char* GetLineFromBuffer (char*) ; 
 int /*<<< orphan*/  IsCommentString (char*) ; 
 scalar_t__ PHY_REG_PG_EXACT_VALUE ; 
 scalar_t__ PHY_REG_PG_RELATIVE_VALUE ; 
 int /*<<< orphan*/  PHY_StoreTxPowerByRate (struct adapter*,int,int,int,int,int,int) ; 
 int RF_1TX ; 
 int RF_2TX ; 
 int RF_3TX ; 
 int RF_4TX ; 
 int _FAIL ; 
 int _SUCCESS ; 
 scalar_t__ eqNByte (char*,...) ; 
 scalar_t__ isAllSpaceOrTab (char*,int) ; 
 int /*<<< orphan*/  phy_DecryptBBPgParaFile (struct adapter*,char*) ; 

__attribute__((used)) static int phy_ParseBBPgParaFile(struct adapter *Adapter, char *buffer)
{
	int	rtStatus = _SUCCESS;
	struct hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	char *szLine, *ptmp;
	u32 u4bRegOffset, u4bRegMask, u4bRegValue;
	u32 u4bMove;
	bool firstLine = true;
	u8 tx_num = 0;
	u8 band = 0, rf_path = 0;

	/* DBG_871X("=====>phy_ParseBBPgParaFile()\n"); */

	if (Adapter->registrypriv.RegDecryptCustomFile == 1)
		phy_DecryptBBPgParaFile(Adapter, buffer);

	ptmp = buffer;
	for (szLine = GetLineFromBuffer(ptmp); szLine != NULL; szLine = GetLineFromBuffer(ptmp)) {
		if (!IsCommentString(szLine)) {
			if (isAllSpaceOrTab(szLine, sizeof(*szLine)))
				continue;

			/*  Get header info (relative value or exact value) */
			if (firstLine) {
				if (eqNByte(szLine, (u8 *)("#[v1]"), 5)) {

					pHalData->odmpriv.PhyRegPgVersion = szLine[3] - '0';
					/* DBG_871X("This is a new format PHY_REG_PG.txt\n"); */
				} else if (eqNByte(szLine, (u8 *)("#[v0]"), 5)) {
					pHalData->odmpriv.PhyRegPgVersion = szLine[3] - '0';
					/* DBG_871X("This is a old format PHY_REG_PG.txt ok\n"); */
				} else {
					DBG_871X("The format in PHY_REG_PG are invalid %s\n", szLine);
					return _FAIL;
				}

				if (eqNByte(szLine + 5, (u8 *)("[Exact]#"), 8)) {
					pHalData->odmpriv.PhyRegPgValueType = PHY_REG_PG_EXACT_VALUE;
					/* DBG_871X("The values in PHY_REG_PG are exact values ok\n"); */
					firstLine = false;
					continue;
				} else if (eqNByte(szLine + 5, (u8 *)("[Relative]#"), 11)) {
					pHalData->odmpriv.PhyRegPgValueType = PHY_REG_PG_RELATIVE_VALUE;
					/* DBG_871X("The values in PHY_REG_PG are relative values ok\n"); */
					firstLine = false;
					continue;
				} else {
					DBG_871X("The values in PHY_REG_PG are invalid %s\n", szLine);
					return _FAIL;
				}
			}

			if (pHalData->odmpriv.PhyRegPgVersion == 0) {
				/*  Get 1st hex value as register offset. */
				if (GetHexValueFromString(szLine, &u4bRegOffset, &u4bMove)) {
					szLine += u4bMove;
					if (u4bRegOffset == 0xffff) /*  Ending. */
						break;

					/*  Get 2nd hex value as register mask. */
					if (GetHexValueFromString(szLine, &u4bRegMask, &u4bMove))
						szLine += u4bMove;
					else
						return _FAIL;

					if (pHalData->odmpriv.PhyRegPgValueType == PHY_REG_PG_RELATIVE_VALUE) {
						/*  Get 3rd hex value as register value. */
						if (GetHexValueFromString(szLine, &u4bRegValue, &u4bMove)) {
							PHY_StoreTxPowerByRate(Adapter, 0, 0, 1, u4bRegOffset, u4bRegMask, u4bRegValue);
							/* DBG_871X("[ADDR] %03X =%08X Mask =%08x\n", u4bRegOffset, u4bRegValue, u4bRegMask); */
						} else
							return _FAIL;
					} else if (pHalData->odmpriv.PhyRegPgValueType == PHY_REG_PG_EXACT_VALUE) {
						u32 combineValue = 0;
						u8 integer = 0, fraction = 0;

						if (GetFractionValueFromString(szLine, &integer, &fraction, &u4bMove))
							szLine += u4bMove;
						else
							return _FAIL;

						integer *= 2;
						if (fraction == 5)
							integer += 1;
						combineValue |= (((integer / 10) << 4) + (integer % 10));
						/* DBG_871X(" %d", integer); */

						if (GetFractionValueFromString(szLine, &integer, &fraction, &u4bMove))
							szLine += u4bMove;
						else
							return _FAIL;

						integer *= 2;
						if (fraction == 5)
							integer += 1;
						combineValue <<= 8;
						combineValue |= (((integer / 10) << 4) + (integer % 10));
						/* DBG_871X(" %d", integer); */

						if (GetFractionValueFromString(szLine, &integer, &fraction, &u4bMove))
							szLine += u4bMove;
						else
							return _FAIL;

						integer *= 2;
						if (fraction == 5)
							integer += 1;
						combineValue <<= 8;
						combineValue |= (((integer / 10) << 4) + (integer % 10));
						/* DBG_871X(" %d", integer); */

						if (GetFractionValueFromString(szLine, &integer, &fraction, &u4bMove))
							szLine += u4bMove;
						else
							return _FAIL;

						integer *= 2;
						if (fraction == 5)
							integer += 1;
						combineValue <<= 8;
						combineValue |= (((integer / 10) << 4) + (integer % 10));
						/* DBG_871X(" %d", integer); */
						PHY_StoreTxPowerByRate(Adapter, 0, 0, 1, u4bRegOffset, u4bRegMask, combineValue);

						/* DBG_871X("[ADDR] 0x%3x = 0x%4x\n", u4bRegOffset, combineValue); */
					}
				}
			} else if (pHalData->odmpriv.PhyRegPgVersion > 0) {
				u32 index = 0;

				if (eqNByte(szLine, "0xffff", 6))
					break;

				if (!eqNByte("#[END]#", szLine, 7)) {
					/*  load the table label info */
					if (szLine[0] == '#') {
						index = 0;
						if (eqNByte(szLine, "#[2.4G]", 7)) {
							band = BAND_ON_2_4G;
							index += 8;
						} else if (eqNByte(szLine, "#[5G]", 5)) {
							band = BAND_ON_5G;
							index += 6;
						} else {
							DBG_871X("Invalid band %s in PHY_REG_PG.txt\n", szLine);
							return _FAIL;
						}

						rf_path = szLine[index] - 'A';
						/* DBG_871X(" Table label Band %d, RfPath %d\n", band, rf_path); */
					} else { /*  load rows of tables */
						if (szLine[1] == '1')
							tx_num = RF_1TX;
						else if (szLine[1] == '2')
							tx_num = RF_2TX;
						else if (szLine[1] == '3')
							tx_num = RF_3TX;
						else if (szLine[1] == '4')
							tx_num = RF_4TX;
						else {
							DBG_871X("Invalid row in PHY_REG_PG.txt %c\n", szLine[1]);
							return _FAIL;
						}

						while (szLine[index] != ']')
							++index;
						++index;/*  skip ] */

						/*  Get 2nd hex value as register offset. */
						szLine += index;
						if (GetHexValueFromString(szLine, &u4bRegOffset, &u4bMove))
							szLine += u4bMove;
						else
							return _FAIL;

						/*  Get 2nd hex value as register mask. */
						if (GetHexValueFromString(szLine, &u4bRegMask, &u4bMove))
							szLine += u4bMove;
						else
							return _FAIL;

						if (pHalData->odmpriv.PhyRegPgValueType == PHY_REG_PG_RELATIVE_VALUE) {
							/*  Get 3rd hex value as register value. */
							if (GetHexValueFromString(szLine, &u4bRegValue, &u4bMove)) {
								PHY_StoreTxPowerByRate(Adapter, band, rf_path, tx_num, u4bRegOffset, u4bRegMask, u4bRegValue);
								/* DBG_871X("[ADDR] %03X (tx_num %d) =%08X Mask =%08x\n", u4bRegOffset, tx_num, u4bRegValue, u4bRegMask); */
							} else
								return _FAIL;
						} else if (pHalData->odmpriv.PhyRegPgValueType == PHY_REG_PG_EXACT_VALUE) {
							u32 combineValue = 0;
							u8 integer = 0, fraction = 0;

							if (GetFractionValueFromString(szLine, &integer, &fraction, &u4bMove))
								szLine += u4bMove;
							else
								return _FAIL;

							integer *= 2;
							if (fraction == 5)
								integer += 1;
							combineValue |= (((integer / 10) << 4) + (integer % 10));
							/* DBG_871X(" %d", integer); */

							if (GetFractionValueFromString(szLine, &integer, &fraction, &u4bMove))
								szLine += u4bMove;
							else
								return _FAIL;

							integer *= 2;
							if (fraction == 5)
								integer += 1;
							combineValue <<= 8;
							combineValue |= (((integer / 10) << 4) + (integer % 10));
							/* DBG_871X(" %d", integer); */

							if (GetFractionValueFromString(szLine, &integer, &fraction, &u4bMove))
								szLine += u4bMove;
							else
								return _FAIL;

							integer *= 2;
							if (fraction == 5)
								integer += 1;
							combineValue <<= 8;
							combineValue |= (((integer / 10) << 4) + (integer % 10));
							/* DBG_871X(" %d", integer); */

							if (GetFractionValueFromString(szLine, &integer, &fraction, &u4bMove))
								szLine += u4bMove;
							else
								return _FAIL;

							integer *= 2;
							if (fraction == 5)
								integer += 1;
							combineValue <<= 8;
							combineValue |= (((integer / 10) << 4) + (integer % 10));
							/* DBG_871X(" %d", integer); */
							PHY_StoreTxPowerByRate(Adapter, band, rf_path, tx_num, u4bRegOffset, u4bRegMask, combineValue);

							/* DBG_871X("[ADDR] 0x%3x (tx_num %d) = 0x%4x\n", u4bRegOffset, tx_num, combineValue); */
						}
					}
				}
			}
		}
	}
	/* DBG_871X("<=====phy_ParseBBPgParaFile()\n"); */
	return rtStatus;
}