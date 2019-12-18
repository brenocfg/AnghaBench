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
 int NUMPRIMES ; 

__attribute__((used)) static int calc_trial_divisions(int bits)
{
    if (bits <= 512)
        return 64;
    else if (bits <= 1024)
        return 128;
    else if (bits <= 2048)
        return 384;
    else if (bits <= 4096)
        return 1024;
    return NUMPRIMES;
}