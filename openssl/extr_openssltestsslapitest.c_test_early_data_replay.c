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
 int test_early_data_replay_int (int,int,int) ; 

__attribute__((used)) static int test_early_data_replay(int idx)
{
    int ret = 1, usecb, confopt;

    for (usecb = 0; usecb < 3; usecb++) {
        for (confopt = 0; confopt < 2; confopt++)
            ret &= test_early_data_replay_int(idx, usecb, confopt);
    }

    return ret;
}