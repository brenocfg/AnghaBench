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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 unsigned int MAX_RESEED_INTERVAL ; 
 scalar_t__ MAX_RESEED_TIME_INTERVAL ; 
 unsigned int master_reseed_interval ; 
 scalar_t__ master_reseed_time_interval ; 
 unsigned int slave_reseed_interval ; 
 scalar_t__ slave_reseed_time_interval ; 

int RAND_DRBG_set_reseed_defaults(
                                  unsigned int _master_reseed_interval,
                                  unsigned int _slave_reseed_interval,
                                  time_t _master_reseed_time_interval,
                                  time_t _slave_reseed_time_interval
                                  )
{
    if (_master_reseed_interval > MAX_RESEED_INTERVAL
        || _slave_reseed_interval > MAX_RESEED_INTERVAL)
        return 0;

    if (_master_reseed_time_interval > MAX_RESEED_TIME_INTERVAL
        || _slave_reseed_time_interval > MAX_RESEED_TIME_INTERVAL)
        return 0;

    master_reseed_interval = _master_reseed_interval;
    slave_reseed_interval = _slave_reseed_interval;

    master_reseed_time_interval = _master_reseed_time_interval;
    slave_reseed_time_interval = _slave_reseed_time_interval;

    return 1;
}