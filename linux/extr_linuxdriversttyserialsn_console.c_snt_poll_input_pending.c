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
 int ia64_sn_console_check (int*) ; 

__attribute__((used)) static int snt_poll_input_pending(void)
{
	int status, input;

	status = ia64_sn_console_check(&input);
	return !status && input;
}