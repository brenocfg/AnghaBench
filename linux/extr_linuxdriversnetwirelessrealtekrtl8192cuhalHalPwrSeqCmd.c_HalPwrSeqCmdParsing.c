#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ WLAN_PWR_CFG ;
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PWR_CFG_BASE (TYPE_1__) ; 
 int GET_PWR_CFG_CMD (TYPE_1__) ; 
 int GET_PWR_CFG_CUT_MASK (TYPE_1__) ; 
 int GET_PWR_CFG_FAB_MASK (TYPE_1__) ; 
 int GET_PWR_CFG_INTF_MASK (TYPE_1__) ; 
 int GET_PWR_CFG_MASK (TYPE_1__) ; 
 int GET_PWR_CFG_OFFSET (TYPE_1__) ; 
 int GET_PWR_CFG_VALUE (TYPE_1__) ; 
 int PWRSEQ_DELAY_US ; 
#define  PWR_CMD_DELAY 132 
#define  PWR_CMD_END 131 
#define  PWR_CMD_POLLING 130 
#define  PWR_CMD_READ 129 
#define  PWR_CMD_WRITE 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FALSE ; 
 int _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 
 int rtw_read8 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  rtw_udelay_os (int) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ ,size_t,int) ; 

u8 HalPwrSeqCmdParsing(
	PADAPTER		padapter,
	u8				CutVersion,
	u8				FabVersion,
	u8				InterfaceType,
	WLAN_PWR_CFG	PwrSeqCmd[])
{
	WLAN_PWR_CFG 	PwrCfgCmd = {0};
	u8				bPollingBit = _FALSE;
	u32				AryIdx = 0;
	u8				value = 0;
	u32				offset = 0;
	u32				pollingCount = 0; // polling autoload done.
	u32				maxPollingCnt = 5000;

	do {
		PwrCfgCmd = PwrSeqCmd[AryIdx];

		RT_TRACE(_module_hal_init_c_ , _drv_info_,
				 ("HalPwrSeqCmdParsing: offset(%#x) cut_msk(%#x) fab_msk(%#x) interface_msk(%#x) base(%#x) cmd(%#x) msk(%#x) value(%#x)\n",
					GET_PWR_CFG_OFFSET(PwrCfgCmd),
					GET_PWR_CFG_CUT_MASK(PwrCfgCmd),
					GET_PWR_CFG_FAB_MASK(PwrCfgCmd),
					GET_PWR_CFG_INTF_MASK(PwrCfgCmd),
					GET_PWR_CFG_BASE(PwrCfgCmd),
					GET_PWR_CFG_CMD(PwrCfgCmd),
					GET_PWR_CFG_MASK(PwrCfgCmd),
					GET_PWR_CFG_VALUE(PwrCfgCmd)));

		//2 Only Handle the command whose FAB, CUT, and Interface are matched
		if ((GET_PWR_CFG_FAB_MASK(PwrCfgCmd) & FabVersion) &&
			(GET_PWR_CFG_CUT_MASK(PwrCfgCmd) & CutVersion) &&
			(GET_PWR_CFG_INTF_MASK(PwrCfgCmd) & InterfaceType))
		{
			switch (GET_PWR_CFG_CMD(PwrCfgCmd))
			{
				case PWR_CMD_READ:
					RT_TRACE(_module_hal_init_c_ , _drv_info_, ("HalPwrSeqCmdParsing: PWR_CMD_READ\n"));
					break;

				case PWR_CMD_WRITE:
					RT_TRACE(_module_hal_init_c_ , _drv_info_, ("HalPwrSeqCmdParsing: PWR_CMD_WRITE\n"));
					offset = GET_PWR_CFG_OFFSET(PwrCfgCmd);

#ifdef CONFIG_SDIO_HCI
					//
					// <Roger_Notes> We should deal with interface specific address mapping for some interfaces, e.g., SDIO interface
					// 2011.07.07.
					//
					if (GET_PWR_CFG_BASE(PwrCfgCmd) == PWR_BASEADDR_SDIO)
					{
						// Read Back SDIO Local value
						value = SdioLocalCmd52Read1Byte(padapter, offset);

						value &= ~(GET_PWR_CFG_MASK(PwrCfgCmd));
						value |= (GET_PWR_CFG_VALUE(PwrCfgCmd) & GET_PWR_CFG_MASK(PwrCfgCmd));

						// Write Back SDIO Local value
						SdioLocalCmd52Write1Byte(padapter, offset, value);
					}
					else
#endif
					{
						// Read the value from system register
						value = rtw_read8(padapter, offset);

						value &= ~(GET_PWR_CFG_MASK(PwrCfgCmd));
						value |= (GET_PWR_CFG_VALUE(PwrCfgCmd) & GET_PWR_CFG_MASK(PwrCfgCmd));

						// Write the value back to sytem register
						rtw_write8(padapter, offset, value);
					}
					break;

				case PWR_CMD_POLLING:
					RT_TRACE(_module_hal_init_c_ , _drv_info_, ("HalPwrSeqCmdParsing: PWR_CMD_POLLING\n"));

					bPollingBit = _FALSE;
					offset = GET_PWR_CFG_OFFSET(PwrCfgCmd);

					do {
#ifdef CONFIG_SDIO_HCI
						if (GET_PWR_CFG_BASE(PwrCfgCmd) == PWR_BASEADDR_SDIO)
							value = SdioLocalCmd52Read1Byte(padapter, offset);
						else
#endif
							value = rtw_read8(padapter, offset);

						value &= GET_PWR_CFG_MASK(PwrCfgCmd);
						if (value == (GET_PWR_CFG_VALUE(PwrCfgCmd) & GET_PWR_CFG_MASK(PwrCfgCmd)))
							bPollingBit = _TRUE;
						else
							rtw_udelay_os(10);

						if (pollingCount++ > maxPollingCnt) {
							RT_TRACE(_module_hal_init_c_ , _drv_err_, ("Fail to polling Offset[%#x]\n", offset));
							return _FALSE;
						}
					} while (!bPollingBit);

					break;

				case PWR_CMD_DELAY:
					RT_TRACE(_module_hal_init_c_ , _drv_info_, ("HalPwrSeqCmdParsing: PWR_CMD_DELAY\n"));
					if (GET_PWR_CFG_VALUE(PwrCfgCmd) == PWRSEQ_DELAY_US)
						rtw_udelay_os(GET_PWR_CFG_OFFSET(PwrCfgCmd));
					else
						rtw_udelay_os(GET_PWR_CFG_OFFSET(PwrCfgCmd)*1000);
					break;

				case PWR_CMD_END:
					// When this command is parsed, end the process
					RT_TRACE(_module_hal_init_c_ , _drv_info_, ("HalPwrSeqCmdParsing: PWR_CMD_END\n"));
					return _TRUE;
					break;

				default:
					RT_TRACE(_module_hal_init_c_ , _drv_err_, ("HalPwrSeqCmdParsing: Unknown CMD!!\n"));
					break;
			}
		}

		AryIdx++;//Add Array Index
	}while(1);

	return _TRUE;
}