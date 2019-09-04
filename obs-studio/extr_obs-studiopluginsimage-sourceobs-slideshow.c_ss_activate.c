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
struct slideshow {scalar_t__ behavior; int restart_on_activate; int use_cut; int pause_on_deactivate; } ;

/* Variables and functions */
 scalar_t__ BEHAVIOR_PAUSE_UNPAUSE ; 
 scalar_t__ BEHAVIOR_STOP_RESTART ; 

__attribute__((used)) static void ss_activate(void *data)
{
	struct slideshow *ss = data;

	if (ss->behavior == BEHAVIOR_STOP_RESTART) {
		ss->restart_on_activate = true;
		ss->use_cut = true;
	} else if (ss->behavior == BEHAVIOR_PAUSE_UNPAUSE) {
		ss->pause_on_deactivate = false;
	}
}