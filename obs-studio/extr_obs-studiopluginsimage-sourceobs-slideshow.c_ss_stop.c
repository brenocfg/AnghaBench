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
struct slideshow {float elapsed; int stop; int paused; scalar_t__ cur_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_transition (struct slideshow*,int) ; 

__attribute__((used)) static void ss_stop(void *data)
{
	struct slideshow *ss = data;

	ss->elapsed = 0.0f;
	ss->cur_item = 0;

	do_transition(ss, true);
	ss->stop = true;
	ss->paused = false;
}