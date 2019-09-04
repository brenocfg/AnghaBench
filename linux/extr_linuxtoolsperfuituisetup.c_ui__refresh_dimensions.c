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

/* Variables and functions */
 int /*<<< orphan*/  SLsmg_reinit_smg () ; 
 int /*<<< orphan*/  SLtt_get_screen_size () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui__lock ; 
 scalar_t__ ui__need_resize ; 

void ui__refresh_dimensions(bool force)
{
	if (force || ui__need_resize) {
		ui__need_resize = 0;
		pthread_mutex_lock(&ui__lock);
		SLtt_get_screen_size();
		SLsmg_reinit_smg();
		pthread_mutex_unlock(&ui__lock);
	}
}