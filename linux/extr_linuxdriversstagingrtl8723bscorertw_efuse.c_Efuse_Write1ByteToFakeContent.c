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
typedef  void* u8 ;
typedef  size_t u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 size_t EFUSE_MAX_HW_SIZE ; 
 void*** fakeBTEfuseContent ; 
 int fakeEfuseBank ; 
 void** fakeEfuseContent ; 

bool
Efuse_Write1ByteToFakeContent(
	struct adapter *padapter,
	u16 	Offset,
	u8 Value)
{
	if (Offset >= EFUSE_MAX_HW_SIZE) {
		return false;
	}
	if (fakeEfuseBank == 0)
		fakeEfuseContent[Offset] = Value;
	else{
		fakeBTEfuseContent[fakeEfuseBank-1][Offset] = Value;
	}
	return true;
}