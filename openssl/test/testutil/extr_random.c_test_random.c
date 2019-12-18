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

/* Variables and functions */
 int* test_random_state ; 

uint32_t test_random(void) {
    static unsigned int pos = 3;

    if (pos == 31)
        pos = 0;
    test_random_state[pos] += test_random_state[(pos + 28) % 31];
    return test_random_state[pos++] / 2;
}