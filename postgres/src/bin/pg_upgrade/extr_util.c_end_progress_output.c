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
 int /*<<< orphan*/  prep_status (char*) ; 

void
end_progress_output(void)
{
	/*
	 * In case nothing printed; pass a space so gcc doesn't complain about
	 * empty format string.
	 */
	prep_status(" ");
}