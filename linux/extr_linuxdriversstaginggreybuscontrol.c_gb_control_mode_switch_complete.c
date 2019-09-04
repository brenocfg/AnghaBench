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
struct gb_control {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_mode_switch_complete (int /*<<< orphan*/ ) ; 

void gb_control_mode_switch_complete(struct gb_control *control)
{
	gb_connection_mode_switch_complete(control->connection);
}