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
typedef  int tBoolean ;

/* Variables and functions */
 int MAP_PRCMHIBRegRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRCMClearSpecialBit (unsigned char) ; 
 int /*<<< orphan*/  RTC_MSEC_U32_REG_ADDR ; 

tBoolean PRCMGetSpecialBit(unsigned char bit)
{
    tBoolean value = (MAP_PRCMHIBRegRead(RTC_MSEC_U32_REG_ADDR) & (1 << bit)) ? true : false;
    // special bits must be cleared immediatelly after reading
    PRCMClearSpecialBit(bit);
    return value;
}