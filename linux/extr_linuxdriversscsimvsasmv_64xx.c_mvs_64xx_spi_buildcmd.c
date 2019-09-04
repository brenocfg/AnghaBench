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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct mvs_info {int dummy; } ;

/* Variables and functions */
 int MV_MAX_U32 ; 

__attribute__((used)) static int mvs_64xx_spi_buildcmd(struct mvs_info *mvi,
			u32      *dwCmd,
			u8       cmd,
			u8       read,
			u8       length,
			u32      addr
			)
{
	u32  dwTmp;

	dwTmp = ((u32)cmd << 24) | ((u32)length << 19);
	if (read)
		dwTmp |= 1U<<23;

	if (addr != MV_MAX_U32) {
		dwTmp |= 1U<<22;
		dwTmp |= (addr & 0x0003FFFF);
	}

	*dwCmd = dwTmp;
	return 0;
}