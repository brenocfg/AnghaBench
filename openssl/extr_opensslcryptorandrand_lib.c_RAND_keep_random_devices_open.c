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
 scalar_t__ RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_rand_init ; 
 int /*<<< orphan*/  rand_init ; 
 int /*<<< orphan*/  rand_pool_keep_random_devices_open (int) ; 

void RAND_keep_random_devices_open(int keep)
{
    if (RUN_ONCE(&rand_init, do_rand_init))
        rand_pool_keep_random_devices_open(keep);
}