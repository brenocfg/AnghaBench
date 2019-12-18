#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* array; } ;
struct slideshow {float elapsed; size_t cur_item; int stop; int paused; TYPE_2__ files; int /*<<< orphan*/  transition; } ;
struct TYPE_3__ {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  obs_transition_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ss_restart(void *data)
{
	struct slideshow *ss = data;

	ss->elapsed = 0.0f;
	ss->cur_item = 0;

	obs_transition_set(ss->transition,
			   ss->files.array[ss->cur_item].source);

	ss->stop = false;
	ss->paused = false;
}