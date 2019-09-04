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
struct ideapad_private {int /*<<< orphan*/  inputdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  sparse_keymap_report_event (int /*<<< orphan*/ ,unsigned long,int,int) ; 

__attribute__((used)) static void ideapad_input_report(struct ideapad_private *priv,
				 unsigned long scancode)
{
	sparse_keymap_report_event(priv->inputdev, scancode, 1, true);
}