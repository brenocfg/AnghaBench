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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int BOOT_FROM_EEPROM ; 
 int /*<<< orphan*/  MSG_8192C (char*,char*) ; 
 int /*<<< orphan*/  REG_9346CR ; 
 int rtw_read16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 GetEEPROMSize8192C(PADAPTER Adapter)
{
	u8	size = 0;
	u32	curRCR;

	curRCR = rtw_read16(Adapter, REG_9346CR);
	size = (curRCR & BOOT_FROM_EEPROM) ? 6 : 4; // 6: EEPROM used is 93C46, 4: boot from E-Fuse.
	
	MSG_8192C("EEPROM type is %s\n", size==4 ? "E-FUSE" : "93C46");
	
	return size;
}