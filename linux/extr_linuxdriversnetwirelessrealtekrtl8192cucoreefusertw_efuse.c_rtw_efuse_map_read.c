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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_GetEfuseDefinition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFUSE_WIFI ; 
 int /*<<< orphan*/  Efuse_PowerSwitch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_EFUSE_MAP_LEN ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  efuse_ReadEFuse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u8 rtw_efuse_map_read(PADAPTER padapter, u16 addr, u16 cnts, u8 *data)
{
	u16	mapLen=0;

	EFUSE_GetEfuseDefinition(padapter, EFUSE_WIFI, TYPE_EFUSE_MAP_LEN, (PVOID)&mapLen, _FALSE);

	if ((addr + cnts) > mapLen)
		return _FAIL;

	Efuse_PowerSwitch(padapter, _FALSE, _TRUE);

	efuse_ReadEFuse(padapter, EFUSE_WIFI, addr, cnts, data, _FALSE);

	Efuse_PowerSwitch(padapter, _FALSE, _FALSE);

	return _SUCCESS;
}