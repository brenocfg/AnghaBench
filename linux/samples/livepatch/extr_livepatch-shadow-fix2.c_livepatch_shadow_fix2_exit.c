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
 int /*<<< orphan*/  SV_COUNTER ; 
 int /*<<< orphan*/  klp_shadow_free_all (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void livepatch_shadow_fix2_exit(void)
{
	/* Cleanup any existing SV_COUNTER shadow variables */
	klp_shadow_free_all(SV_COUNTER, NULL);
}