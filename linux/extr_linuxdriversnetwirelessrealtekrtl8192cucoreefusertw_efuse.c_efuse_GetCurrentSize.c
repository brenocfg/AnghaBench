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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_WIFI ; 
 int /*<<< orphan*/  Efuse_GetCurrentSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Efuse_PowerSwitch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _TRUE ; 

u8 efuse_GetCurrentSize(PADAPTER padapter, u16 *size)
{
	Efuse_PowerSwitch(padapter, _FALSE, _TRUE);
	*size = Efuse_GetCurrentSize(padapter, EFUSE_WIFI, _FALSE);
	Efuse_PowerSwitch(padapter, _FALSE, _FALSE);

	return _SUCCESS;
}