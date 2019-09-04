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
typedef  scalar_t__ time_t ;
struct TYPE_3__ {scalar_t__ reseed_time_interval; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 scalar_t__ MAX_RESEED_TIME_INTERVAL ; 

int RAND_DRBG_set_reseed_time_interval(RAND_DRBG *drbg, time_t interval)
{
    if (interval > MAX_RESEED_TIME_INTERVAL)
        return 0;
    drbg->reseed_time_interval = interval;
    return 1;
}