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
struct eeepc_laptop {int /*<<< orphan*/  inputdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  sparse_keymap_report_event (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void eeepc_input_notify(struct eeepc_laptop *eeepc, int event)
{
	if (!eeepc->inputdev)
		return;
	if (!sparse_keymap_report_event(eeepc->inputdev, event, 1, true))
		pr_info("Unknown key %x pressed\n", event);
}