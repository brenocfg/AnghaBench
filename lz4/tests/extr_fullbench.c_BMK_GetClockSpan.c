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
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 scalar_t__ clock () ; 

__attribute__((used)) static clock_t BMK_GetClockSpan( clock_t clockStart )
{
    return clock() - clockStart;   /* works even if overflow; max span ~30 mn */
}