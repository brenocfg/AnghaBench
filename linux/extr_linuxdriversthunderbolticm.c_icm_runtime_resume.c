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
struct tb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  icm_complete (struct tb*) ; 

__attribute__((used)) static int icm_runtime_resume(struct tb *tb)
{
	/*
	 * We can reuse the same resume functionality than with system
	 * suspend.
	 */
	icm_complete(tb);
	return 0;
}