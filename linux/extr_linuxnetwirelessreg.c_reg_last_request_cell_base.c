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
 int /*<<< orphan*/  get_last_request () ; 
 int reg_request_cell_base (int /*<<< orphan*/ ) ; 

bool reg_last_request_cell_base(void)
{
	return reg_request_cell_base(get_last_request());
}