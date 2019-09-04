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
typedef  size_t u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 size_t EFUSE_MAX_HW_SIZE ; 
 int /*<<< orphan*/ ** fakeBTEfuseContent ; 
 int fakeEfuseBank ; 
 int /*<<< orphan*/ * fakeEfuseContent ; 

bool
Efuse_Read1ByteFromFakeContent(
	struct adapter *padapter,
	u16 	Offset,
	u8 *Value)
{
	if (Offset >= EFUSE_MAX_HW_SIZE) {
		return false;
	}
	/* DbgPrint("Read fake content, offset = %d\n", Offset); */
	if (fakeEfuseBank == 0)
		*Value = fakeEfuseContent[Offset];
	else
		*Value = fakeBTEfuseContent[fakeEfuseBank-1][Offset];
	return true;
}