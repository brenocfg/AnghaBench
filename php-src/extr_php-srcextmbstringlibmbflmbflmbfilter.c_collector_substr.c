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
struct collector_substr_data {scalar_t__ output; scalar_t__ stop; scalar_t__ start; TYPE_1__* next_filter; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* filter_function ) (int,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,TYPE_1__*) ; 

__attribute__((used)) static int
collector_substr(int c, void* data)
{
	struct collector_substr_data *pc = (struct collector_substr_data*)data;

	if (pc->output >= pc->stop) {
		return -1;
	}

	if (pc->output >= pc->start) {
		(*pc->next_filter->filter_function)(c, pc->next_filter);
	}

	pc->output++;

	return c;
}