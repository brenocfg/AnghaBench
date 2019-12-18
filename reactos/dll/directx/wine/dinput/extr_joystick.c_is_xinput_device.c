#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_3__ {int dwAxes; int dwButtons; } ;
typedef  TYPE_1__ DIDEVCAPS ;
typedef  int BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* PID_XBOX_CONTROLLERS ; 
 int TRUE ; 
 scalar_t__ VID_MICROSOFT ; 

BOOL is_xinput_device(const DIDEVCAPS *devcaps, WORD vid, WORD pid)
{
    int i;

    if (vid == VID_MICROSOFT)
    {
        for (i = 0; i < ARRAY_SIZE(PID_XBOX_CONTROLLERS); i++)
            if (pid == PID_XBOX_CONTROLLERS[i]) return TRUE;
    }

    return (devcaps->dwAxes == 6 && devcaps->dwButtons >= 14);
}