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
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  running_helpers ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static void helper_lock(void)
{
	atomic_inc(&running_helpers);
	smp_mb__after_atomic();
}