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
struct TYPE_2__ {scalar_t__ num; } ;
struct slideshow {scalar_t__ cur_item; TYPE_1__ files; int /*<<< orphan*/  transition; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_transition (struct slideshow*,int) ; 
 float obs_transition_get_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ss_next_slide(void *data)
{
	struct slideshow *ss = data;

	if (!ss->files.num || obs_transition_get_time(ss->transition) < 1.0f)
		return;

	if (++ss->cur_item >= ss->files.num)
		ss->cur_item = 0;

	do_transition(ss, false);
}