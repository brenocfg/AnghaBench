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
 int /*<<< orphan*/  KASAN_BIT_MULTI_SHOT ; 
 int /*<<< orphan*/  kasan_flags ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool kasan_save_enable_multi_shot(void)
{
	return test_and_set_bit(KASAN_BIT_MULTI_SHOT, &kasan_flags);
}