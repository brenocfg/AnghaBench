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
struct tep_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pevent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct tep_event* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct tep_event* tep_find_event (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ tevent ; 
 int /*<<< orphan*/  tevent_initialized ; 
 scalar_t__ trace_event__init2 () ; 

struct tep_event *trace_event__tp_format_id(int id)
{
	if (!tevent_initialized && trace_event__init2())
		return ERR_PTR(-ENOMEM);

	return tep_find_event(tevent.pevent, id);
}