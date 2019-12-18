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
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DI8DEVTYPEJOYSTICK_STANDARD ; 
 int DI8DEVTYPE_GAMEPAD ; 
 int DI8DEVTYPE_JOYSTICK ; 
 int DIDEVTYPEJOYSTICK_GAMEPAD ; 
 int DIDEVTYPEJOYSTICK_TRADITIONAL ; 
 int DIDEVTYPE_JOYSTICK ; 

DWORD get_device_type(DWORD version, BOOL is_joystick)
{
    if (is_joystick)
        return version >= 0x0800 ? DI8DEVTYPE_JOYSTICK | (DI8DEVTYPEJOYSTICK_STANDARD << 8) :
                    DIDEVTYPE_JOYSTICK | (DIDEVTYPEJOYSTICK_TRADITIONAL << 8);

    return version >= 0x0800 ? DI8DEVTYPE_GAMEPAD | (DI8DEVTYPEJOYSTICK_STANDARD << 8) :
                DIDEVTYPE_JOYSTICK | (DIDEVTYPEJOYSTICK_GAMEPAD << 8);
}