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
typedef  int uint32_t ;
struct xdaliclock {int dummy; } ;

/* Variables and functions */
 int FRAMES_PER_SECOND ; 

uint32_t xdaliclock_get_frame_time(const struct xdaliclock *xdc
                                   __attribute__((unused)))
{
    return 1000 / FRAMES_PER_SECOND;
}