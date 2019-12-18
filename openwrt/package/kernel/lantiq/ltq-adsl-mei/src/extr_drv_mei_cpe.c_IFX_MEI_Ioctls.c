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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  base_address ;
struct TYPE_8__ {int major; int /*<<< orphan*/  minor; } ;
struct TYPE_7__ {int /*<<< orphan*/  iData; int /*<<< orphan*/  iAddress; } ;
struct TYPE_5__ {int* RxMessage; int /*<<< orphan*/ * TxMessage; } ;
struct TYPE_6__ {TYPE_1__ msg; } ;
typedef  TYPE_2__ DSL_DEV_WinHost_Message_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Version_t ;
typedef  TYPE_3__ DSL_DEV_MeiReg_t ;
typedef  int /*<<< orphan*/  DSL_DEV_HwVersion_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMAZON_SE_MEI_ARC_MUX_Test () ; 
 int DSL_BSP_SendCMV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  DSL_CMV_GROUP_STAT ; 
 int /*<<< orphan*/  DSL_CPU_HALT ; 
 int /*<<< orphan*/  DSL_CPU_RESET ; 
 int /*<<< orphan*/  DSL_CPU_RUN ; 
 int DSL_DEV_MEI_ERR_FAILURE ; 
 int DSL_DEV_MEI_ERR_SUCCESS ; 
 int DSL_DEV_STAT_CODESWAP_COMPLETE ; 
#define  DSL_FIO_ARC_MUX_TEST 144 
#define  DSL_FIO_BSP_BOOTDOWNLOAD 143 
#define  DSL_FIO_BSP_CMV_READ 142 
#define  DSL_FIO_BSP_CMV_WINHOST 141 
#define  DSL_FIO_BSP_CMV_WRITE 140 
#define  DSL_FIO_BSP_DSL_START 139 
#define  DSL_FIO_BSP_FREE_RESOURCE 138 
#define  DSL_FIO_BSP_GET_BASE_ADDRESS 137 
#define  DSL_FIO_BSP_GET_CHIP_INFO 136 
#define  DSL_FIO_BSP_GET_VERSION 135 
#define  DSL_FIO_BSP_HALT 134 
#define  DSL_FIO_BSP_IS_MODEM_READY 133 
#define  DSL_FIO_BSP_JTAG_ENABLE 132 
#define  DSL_FIO_BSP_REBOOT 131 
#define  DSL_FIO_BSP_REMOTE 130 
#define  DSL_FIO_BSP_RESET 129 
#define  DSL_FIO_BSP_RUN 128 
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  FREE_SHOWTIME ; 
 int /*<<< orphan*/  H2D_CMV_READ ; 
 int IFX_MEI_AdslMailboxIRQEnable (int /*<<< orphan*/ *,int) ; 
 int IFX_MEI_ArcJtagEnable (int /*<<< orphan*/ *,int) ; 
 int IFX_MEI_CpuModeSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_MEI_DFEMemoryFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_MEI_DMSG (char*,...) ; 
 int IFX_MEI_DownloadBootCode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*,...) ; 
 int /*<<< orphan*/  IFX_MEI_IoctlCopyFrom (int,char*,char*,int) ; 
 int /*<<< orphan*/  IFX_MEI_IoctlCopyTo (int,char*,char*,int) ; 
 int IFX_MEI_IsModemReady (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFX_MEI_RunAdslModem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LTQ_MEI_BASE_ADDR ; 
 int /*<<< orphan*/ * LTQ_MPS_CHIPID ; 
 int /*<<< orphan*/  LTQ_MPS_CHIPID_VERSION_GET (int /*<<< orphan*/ ) ; 
 int MSG_LENGTH ; 
 int /*<<< orphan*/  YES_REPLY ; 
 TYPE_4__ bsp_chip_info ; 
 int /*<<< orphan*/  bsp_mei_version ; 
 int /*<<< orphan*/  makeCMV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
IFX_MEI_Ioctls (DSL_DEV_Device_t * pDev, int from_kernel, unsigned int command, unsigned long lon)
{
	int i = 0;
	int meierr = DSL_DEV_MEI_ERR_SUCCESS;
	u32 base_address = LTQ_MEI_BASE_ADDR;
	DSL_DEV_WinHost_Message_t winhost_msg, m;
//	DSL_DEV_MeiDebug_t debugrdwr;
	DSL_DEV_MeiReg_t regrdwr;

	switch (command) {

	case DSL_FIO_BSP_CMV_WINHOST:
		IFX_MEI_IoctlCopyFrom (from_kernel, (char *) winhost_msg.msg.TxMessage,
					     (char *) lon, MSG_LENGTH * 2);

		if ((meierr = DSL_BSP_SendCMV (pDev, winhost_msg.msg.TxMessage, YES_REPLY,
					   winhost_msg.msg.RxMessage)) != DSL_DEV_MEI_ERR_SUCCESS) {
			IFX_MEI_EMSG ("WINHOST CMV fail :TxMessage:%X %X %X %X, RxMessage:%X %X %X %X %X\n",
				 winhost_msg.msg.TxMessage[0], winhost_msg.msg.TxMessage[1], winhost_msg.msg.TxMessage[2], winhost_msg.msg.TxMessage[3],
				 winhost_msg.msg.RxMessage[0], winhost_msg.msg.RxMessage[1], winhost_msg.msg.RxMessage[2], winhost_msg.msg.RxMessage[3],
				 winhost_msg.msg.RxMessage[4]);
			meierr = DSL_DEV_MEI_ERR_FAILURE;
		}
		else {
			IFX_MEI_IoctlCopyTo (from_kernel, (char *) lon,
						   (char *) winhost_msg.msg.RxMessage,
						   MSG_LENGTH * 2);
		}
		break;

	case DSL_FIO_BSP_CMV_READ:
		IFX_MEI_IoctlCopyFrom (from_kernel, (char *) (&regrdwr),
					     (char *) lon, sizeof (DSL_DEV_MeiReg_t));

		IFX_MEI_LongWordRead ((u32) regrdwr.iAddress,
					    (u32 *) & (regrdwr.iData));

		IFX_MEI_IoctlCopyTo (from_kernel, (char *) lon,
					   (char *) (&regrdwr),
					   sizeof (DSL_DEV_MeiReg_t));

		break;

	case DSL_FIO_BSP_CMV_WRITE:
		IFX_MEI_IoctlCopyFrom (from_kernel, (char *) (&regrdwr),
					     (char *) lon, sizeof (DSL_DEV_MeiReg_t));

		IFX_MEI_LongWordWrite ((u32) regrdwr.iAddress,
					     regrdwr.iData);
		break;

	case DSL_FIO_BSP_GET_BASE_ADDRESS:
		IFX_MEI_IoctlCopyTo (from_kernel, (char *) lon,
					   (char *) (&base_address),
					   sizeof (base_address));
		break;

	case DSL_FIO_BSP_IS_MODEM_READY:
		i = IFX_MEI_IsModemReady (pDev);
		IFX_MEI_IoctlCopyTo (from_kernel, (char *) lon,
					   (char *) (&i), sizeof (int));
		meierr = DSL_DEV_MEI_ERR_SUCCESS;
		break;
	case DSL_FIO_BSP_RESET:
	case DSL_FIO_BSP_REBOOT:
		meierr = IFX_MEI_CpuModeSet (pDev, DSL_CPU_RESET);
		meierr = IFX_MEI_CpuModeSet (pDev, DSL_CPU_HALT);
		break;

	case DSL_FIO_BSP_HALT:
		meierr = IFX_MEI_CpuModeSet (pDev, DSL_CPU_HALT);
		break;

	case DSL_FIO_BSP_RUN:
		meierr = IFX_MEI_CpuModeSet (pDev, DSL_CPU_RUN);
		break;
	case DSL_FIO_BSP_BOOTDOWNLOAD:
		meierr = IFX_MEI_DownloadBootCode (pDev);
		break;
	case DSL_FIO_BSP_JTAG_ENABLE:
		meierr = IFX_MEI_ArcJtagEnable (pDev, 1);
		break;

	case DSL_FIO_BSP_REMOTE:
		IFX_MEI_IoctlCopyFrom (from_kernel, (char *) (&i),
					     (char *) lon, sizeof (int));

		meierr = IFX_MEI_AdslMailboxIRQEnable (pDev, i);
		break;

	case DSL_FIO_BSP_DSL_START:
		IFX_MEI_DMSG("DSL_FIO_BSP_DSL_START\n");
		if ((meierr = IFX_MEI_RunAdslModem (pDev)) != DSL_DEV_MEI_ERR_SUCCESS) {
			IFX_MEI_EMSG ("IFX_MEI_RunAdslModem() error...");
			meierr = DSL_DEV_MEI_ERR_FAILURE;
		}
		break;

/*	case DSL_FIO_BSP_DEBUG_READ:
	case DSL_FIO_BSP_DEBUG_WRITE:
		IFX_MEI_IoctlCopyFrom (from_kernel,
					     (char *) (&debugrdwr),
					     (char *) lon,
					     sizeof (debugrdwr));

		if (command == DSL_FIO_BSP_DEBUG_READ)
			meierr = DSL_BSP_MemoryDebugAccess (pDev,
								 DSL_BSP_MEMORY_READ,
								 debugrdwr.
								 iAddress,
								 debugrdwr.
								 buffer,
								 debugrdwr.
								 iCount);
		else
			meierr = DSL_BSP_MemoryDebugAccess (pDev,
								 DSL_BSP_MEMORY_WRITE,
								 debugrdwr.
								 iAddress,
								 debugrdwr.
								 buffer,
								 debugrdwr.
								 iCount);

		IFX_MEI_IoctlCopyTo (from_kernel, (char *) lon, (char *) (&debugrdwr), sizeof (debugrdwr));
		break;*/
	case DSL_FIO_BSP_GET_VERSION:
		IFX_MEI_IoctlCopyTo (from_kernel, (char *) lon, (char *) (&bsp_mei_version), sizeof (DSL_DEV_Version_t));
		break;

#define LTQ_MPS_CHIPID_VERSION_GET(value)  (((value) >> 28) & ((1 << 4) - 1))
	case DSL_FIO_BSP_GET_CHIP_INFO:
                bsp_chip_info.major = 1;
                bsp_chip_info.minor = LTQ_MPS_CHIPID_VERSION_GET(*LTQ_MPS_CHIPID);
                IFX_MEI_IoctlCopyTo (from_kernel, (char *) lon, (char *) (&bsp_chip_info), sizeof (DSL_DEV_HwVersion_t));
                meierr = DSL_DEV_MEI_ERR_SUCCESS;
		break;

        case DSL_FIO_BSP_FREE_RESOURCE:
                makeCMV (H2D_CMV_READ, DSL_CMV_GROUP_STAT, 4, 0, 1, NULL, m.msg.TxMessage);
                if (DSL_BSP_SendCMV (pDev, m.msg.TxMessage, YES_REPLY, m.msg.RxMessage) != DSL_DEV_MEI_ERR_SUCCESS) {
                        meierr = DSL_DEV_MEI_ERR_FAILURE;
                        return -EIO;
                }
                IFX_MEI_DMSG("RxMessage[4] = %#x\n", m.msg.RxMessage[4]);
                if (!(m.msg.RxMessage[4] & DSL_DEV_STAT_CODESWAP_COMPLETE)) {
                        meierr = DSL_DEV_MEI_ERR_FAILURE;
                        return -EAGAIN;
                }
                IFX_MEI_DMSG("Freeing all memories marked FREE_SHOWTIME\n");
                IFX_MEI_DFEMemoryFree (pDev, FREE_SHOWTIME);
                meierr = DSL_DEV_MEI_ERR_SUCCESS;
		break;
#ifdef CONFIG_IFXMIPS_AMAZON_SE
	case DSL_FIO_ARC_MUX_TEST:
		AMAZON_SE_MEI_ARC_MUX_Test();
		break;
#endif
	default:
//		IFX_MEI_EMSG("Invalid IOCTL command: %d\n");
		break;
	}
	return meierr;
}