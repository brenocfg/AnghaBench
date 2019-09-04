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
struct kbd_repeat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_handler_for_each_handle (int /*<<< orphan*/ *,struct kbd_repeat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_handler ; 
 int /*<<< orphan*/  kbd_rate_helper ; 

int kbd_rate(struct kbd_repeat *rpt)
{
	struct kbd_repeat data[2] = { *rpt };

	input_handler_for_each_handle(&kbd_handler, data, kbd_rate_helper);
	*rpt = data[1];	/* Copy currently used settings */

	return 0;
}