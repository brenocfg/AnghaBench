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
 int /*<<< orphan*/  RAND_set_rand_method (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuzz_rand_method ; 

void FuzzerSetRand(void)
{
    RAND_set_rand_method(&fuzz_rand_method);
}