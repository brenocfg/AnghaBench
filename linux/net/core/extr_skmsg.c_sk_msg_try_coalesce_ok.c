#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int end; int start; } ;
struct sk_msg {TYPE_1__ sg; } ;

/* Variables and functions */

__attribute__((used)) static bool sk_msg_try_coalesce_ok(struct sk_msg *msg, int elem_first_coalesce)
{
	if (msg->sg.end > msg->sg.start &&
	    elem_first_coalesce < msg->sg.end)
		return true;

	if (msg->sg.end < msg->sg.start &&
	    (elem_first_coalesce > msg->sg.start ||
	     elem_first_coalesce < msg->sg.end))
		return true;

	return false;
}