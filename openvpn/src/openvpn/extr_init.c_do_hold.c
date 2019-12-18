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

/* Variables and functions */
 scalar_t__ management ; 
 scalar_t__ management_hold (scalar_t__,int) ; 

__attribute__((used)) static bool
do_hold(int holdtime)
{
#ifdef ENABLE_MANAGEMENT
    if (management)
    {
        /* block until management hold is released */
        if (management_hold(management, holdtime))
        {
            return true;
        }
    }
#endif
    return false;
}