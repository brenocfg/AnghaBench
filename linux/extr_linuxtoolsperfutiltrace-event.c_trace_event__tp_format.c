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
struct event_format {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct event_format* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tevent_initialized ; 
 struct event_format* tp_format (char const*,char const*) ; 
 scalar_t__ trace_event__init2 () ; 

struct event_format*
trace_event__tp_format(const char *sys, const char *name)
{
	if (!tevent_initialized && trace_event__init2())
		return ERR_PTR(-ENOMEM);

	return tp_format(sys, name);
}