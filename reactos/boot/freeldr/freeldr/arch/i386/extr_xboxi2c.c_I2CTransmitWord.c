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
typedef  int USHORT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  WriteToSMBus (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static BOOLEAN
I2CTransmitWord(UCHAR bPicAddressI2cFormat, USHORT wDataToWrite)
{
  return WriteToSMBus(bPicAddressI2cFormat,(wDataToWrite>>8)&0xff,1,(wDataToWrite&0xff));
}