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
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_WIFI ; 
 int /*<<< orphan*/  hal_ReadEFuse_BT (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  hal_ReadEFuse_WiFi (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void Hal_ReadEFuse(
	struct adapter *padapter,
	u8 efuseType,
	u16 _offset,
	u16 _size_byte,
	u8 *pbuf,
	bool bPseudoTest
)
{
	if (efuseType == EFUSE_WIFI)
		hal_ReadEFuse_WiFi(padapter, _offset, _size_byte, pbuf, bPseudoTest);
	else
		hal_ReadEFuse_BT(padapter, _offset, _size_byte, pbuf, bPseudoTest);
}