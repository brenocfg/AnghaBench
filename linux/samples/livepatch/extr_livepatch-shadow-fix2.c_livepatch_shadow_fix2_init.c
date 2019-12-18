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
 int klp_enable_patch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  patch ; 

__attribute__((used)) static int livepatch_shadow_fix2_init(void)
{
	return klp_enable_patch(&patch);
}