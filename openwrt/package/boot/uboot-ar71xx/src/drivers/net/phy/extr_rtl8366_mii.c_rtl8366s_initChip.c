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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  RTL8366S_LEDCONF_LEDFORCE ; 
 int RTL8366S_LED_GROUP_MAX ; 
#define  RTL8366S_MODEL_8366SR 128 
 int /*<<< orphan*/  RTL8366S_MODEL_ID_REG ; 
 int const RTL8366S_PHY_ACCESS_CTRL_REG ; 
 int const RTL8366S_PHY_CTRL_WRITE ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rtl8366_readRegister (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rtl8366_writeRegister (int const,int const) ; 
 scalar_t__ rtl8366s_getLedConfig (int,int /*<<< orphan*/ *) ; 
 scalar_t__ rtl8366s_setLedConfig (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl8366s_setLedForceValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int rtl8366s_initChip(void)
{
    uint32_t ledGroup, i = 0;
    uint16_t regData;
    uint8_t ledData[RTL8366S_LED_GROUP_MAX];
	const uint16_t (*chipData)[2];

	const uint16_t chipB[][2] =
	{
		{0x0000,	0x0038},{0x8100,	0x1B37},{0xBE2E,	0x7B9F},{0xBE2B,	0xA4C8},
		{0xBE74,	0xAD14},{0xBE2C,	0xDC00},{0xBE69,	0xD20F},{0xBE3B,	0xB414},
		{0xBE24,	0x0000},{0xBE23,	0x00A1},{0xBE22,	0x0008},{0xBE21,	0x0120},
		{0xBE20,	0x1000},{0xBE24,	0x0800},{0xBE24,	0x0000},{0xBE24,	0xF000},
		{0xBE23,	0xDF01},{0xBE22,	0xDF20},{0xBE21,	0x101A},{0xBE20,	0xA0FF},
		{0xBE24,	0xF800},{0xBE24,	0xF000},{0x0242,	0x02BF},{0x0245,	0x02BF},
		{0x0248,	0x02BF},{0x024B,	0x02BF},{0x024E,	0x02BF},{0x0251,	0x02BF},
		{0x0230,	0x0A32},{0x0233,	0x0A32},{0x0236,	0x0A32},{0x0239,	0x0A32},
		{0x023C,	0x0A32},{0x023F,	0x0A32},{0x0254,	0x0A3F},{0x0255,	0x0064},
		{0x0256,	0x0A3F},{0x0257,	0x0064},{0x0258,	0x0A3F},{0x0259,	0x0064},
		{0x025A,	0x0A3F},{0x025B,	0x0064},{0x025C,	0x0A3F},{0x025D,	0x0064},
		{0x025E,	0x0A3F},{0x025F,	0x0064},{0x0260,	0x0178},{0x0261,	0x01F4},
		{0x0262,	0x0320},{0x0263,	0x0014},{0x021D,	0x9249},{0x021E,	0x0000},
		{0x0100,	0x0004},{0xBE4A,	0xA0B4},{0xBE40,	0x9C00},{0xBE41,	0x501D},
		{0xBE48,	0x3602},{0xBE47,	0x8051},{0xBE4C,	0x6465},{0x8000,	0x1F00},
		{0x8001,	0x000C},{0x8008,	0x0000},{0x8007,	0x0000},{0x800C,	0x00A5},
		{0x8101,	0x02BC},{0xBE53,	0x0005},{0x8E45,	0xAFE8},{0x8013,	0x0005},
		{0xBE4B,	0x6700},{0x800B,	0x7000},{0xBE09,	0x0E00},
		{0xFFFF, 0xABCD}
	};

    const uint16_t chipDefault[][2] =
    {
        {0x0242, 0x02BF},{0x0245, 0x02BF},{0x0248, 0x02BF},{0x024B, 0x02BF},
		{0x024E, 0x02BF},{0x0251, 0x02BF},
		{0x0254, 0x0A3F},{0x0256, 0x0A3F},{0x0258, 0x0A3F},{0x025A, 0x0A3F},
		{0x025C, 0x0A3F},{0x025E, 0x0A3F},
		{0x0263, 0x007C},{0x0100, 0x0004},
		{0xBE5B, 0x3500},{0x800E, 0x200F},{0xBE1D, 0x0F00},{0x8001, 0x5011},
		{0x800A, 0xA2F4},{0x800B, 0x17A3},{0xBE4B, 0x17A3},{0xBE41, 0x5011},
		{0xBE17, 0x2100},{0x8000, 0x8304},{0xBE40, 0x8304},{0xBE4A, 0xA2F4},
		{0x800C, 0xA8D5},{0x8014, 0x5500},{0x8015, 0x0004},{0xBE4C, 0xA8D5},
		{0xBE59, 0x0008},{0xBE09, 0x0E00},{0xBE36, 0x1036},{0xBE37, 0x1036},
		{0x800D, 0x00FF},{0xBE4D, 0x00FF},
		{0xFFFF, 0xABCD}
    };

	DBG("rtl8366s_initChip\n");

    /* save current led config and set to led force */
    for (ledGroup = 0; ledGroup < RTL8366S_LED_GROUP_MAX; ledGroup++) {
        if (rtl8366s_getLedConfig(ledGroup, &ledData[ledGroup]))
            return -1;

        if (rtl8366s_setLedConfig(ledGroup, RTL8366S_LEDCONF_LEDFORCE))
            return -1;
    }

    if (rtl8366s_setLedForceValue(0,0,0,0))
        return -1;

    if (rtl8366_readRegister(RTL8366S_MODEL_ID_REG, &regData))
        return -1;

	switch (regData)
	{
		case 0x0000:
			chipData = chipB;
			break;

		case RTL8366S_MODEL_8366SR:
			chipData = chipDefault;
			break;

		default:
			printf("rtl8366s_initChip: unsupported chip found!\n");
			return -1;
	}

    DBG("rtl8366s_initChip: found %x chip\n", regData);

    while ((chipData[i][0] != 0xFFFF) && (chipData[i][1] != 0xABCD)) {

        /* phy settings*/
        if ((chipData[i][0] & 0xBE00) == 0xBE00) {
            if (rtl8366_writeRegister(RTL8366S_PHY_ACCESS_CTRL_REG,
                                      RTL8366S_PHY_CTRL_WRITE))
                return -1;
        }

        if (rtl8366_writeRegister(chipData[i][0], chipData[i][1]))
            return -1;

        i++;
    }

    /* chip needs some time */
    udelay(100 * 1000);

    /* restore led config */
    for (ledGroup = 0; ledGroup < RTL8366S_LED_GROUP_MAX; ledGroup++) {
        if (rtl8366s_setLedConfig(ledGroup, ledData[ledGroup]))
            return -1;
    }

    return 0;
}