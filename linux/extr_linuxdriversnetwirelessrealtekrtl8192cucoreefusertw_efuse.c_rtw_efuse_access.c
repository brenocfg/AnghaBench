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
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_GetEfuseDefinition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  EFUSE_WIFI ; 
 int /*<<< orphan*/  Efuse_PowerSwitch (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TYPE_AVAILABLE_EFUSE_BYTES_TOTAL ; 
 int /*<<< orphan*/  TYPE_EFUSE_REAL_CONTENT_LEN ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 scalar_t__ efuse_read8 (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 scalar_t__ efuse_write8 (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

u8 rtw_efuse_access(PADAPTER padapter, u8 bWrite, u16 start_addr, u16 cnts, u8 *data)
{
	int i = 0;
	u16	real_content_len = 0, max_available_size = 0;
	u8 res = _FAIL ;
	u8 (*rw8)(PADAPTER, u16, u8*);

	EFUSE_GetEfuseDefinition(padapter, EFUSE_WIFI, TYPE_EFUSE_REAL_CONTENT_LEN, (PVOID)&real_content_len, _FALSE);
	EFUSE_GetEfuseDefinition(padapter, EFUSE_WIFI, TYPE_AVAILABLE_EFUSE_BYTES_TOTAL, (PVOID)&max_available_size, _FALSE);

	if (start_addr > real_content_len)
		return _FAIL;

	if (_TRUE == bWrite) {
		if ((start_addr + cnts) > max_available_size)
			return _FAIL;
		rw8 = &efuse_write8;
	} else
		rw8 = &efuse_read8;

	Efuse_PowerSwitch(padapter, bWrite, _TRUE);

	// e-fuse one byte read / write
	for (i = 0; i < cnts; i++) {
		if (start_addr >= real_content_len) {
			res = _FAIL;
			break;
		}

		res = rw8(padapter, start_addr++, data++);
		if (_FAIL == res) break;
	}

	Efuse_PowerSwitch(padapter, bWrite, _FALSE);

	return res;
}