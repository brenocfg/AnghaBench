#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  int u32 ;
struct TYPE_2__ {int* mac_addr; } ;
struct _adapter {TYPE_1__ eeprompriv; int /*<<< orphan*/  pnetdev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MACID ; 
 int RCR ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 
 int r8712_read32 (struct _adapter*,int) ; 
 int r8712_read8 (struct _adapter*,int) ; 
 int /*<<< orphan*/  r8712_write32 (struct _adapter*,int,int) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,int,int) ; 
 scalar_t__ rtl8712_dl_fw (struct _adapter*) ; 

uint rtl8712_hal_init(struct _adapter *padapter)
{
	u32 val32;
	int i;

	/* r8712 firmware download */
	if (rtl8712_dl_fw(padapter) != _SUCCESS)
		return _FAIL;

	netdev_info(padapter->pnetdev, "1 RCR=0x%x\n",
		    r8712_read32(padapter, RCR));
	val32 = r8712_read32(padapter, RCR);
	r8712_write32(padapter, RCR, (val32 | BIT(26))); /* Enable RX TCP
							  * Checksum offload
							  */
	netdev_info(padapter->pnetdev, "2 RCR=0x%x\n",
		    r8712_read32(padapter, RCR));
	val32 = r8712_read32(padapter, RCR);
	r8712_write32(padapter, RCR, (val32 | BIT(25))); /* Append PHY status */
	val32 = r8712_read32(padapter, 0x10250040);
	r8712_write32(padapter,  0x10250040, (val32 & 0x00FFFFFF));
	/* for usb rx aggregation */
	r8712_write8(padapter, 0x102500B5, r8712_read8(padapter, 0x102500B5) |
	       BIT(0)); /* page = 128bytes */
	r8712_write8(padapter, 0x102500BD, r8712_read8(padapter, 0x102500BD) |
	       BIT(7)); /* enable usb rx aggregation */
	r8712_write8(padapter, 0x102500D9, 1); /* TH=1 => means that invalidate
						*  usb rx aggregation
						*/
	r8712_write8(padapter, 0x1025FE5B, 0x04); /* 1.7ms/4 */
	/* Fix the RX FIFO issue(USB error) */
	r8712_write8(padapter, 0x1025fe5C, r8712_read8(padapter, 0x1025fe5C)
		     | BIT(7));
	for (i = 0; i < 6; i++)
		padapter->eeprompriv.mac_addr[i] = r8712_read8(padapter,
							       MACID + i);
	return _SUCCESS;
}