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
 int /*<<< orphan*/  SLsmg_fill_region (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  SLsmg_refresh () ; 
 int /*<<< orphan*/  SLsmg_set_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLtt_Screen_Cols ; 
 int SLtt_Screen_Rows ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui__lock ; 
 int /*<<< orphan*/  ui__refresh_dimensions (int) ; 
 scalar_t__ use_browser ; 

__attribute__((used)) static void tui_progress__finish(void)
{
	int y;

	if (use_browser <= 0)
		return;

	ui__refresh_dimensions(false);
	pthread_mutex_lock(&ui__lock);
	y = SLtt_Screen_Rows / 2 - 2;
	SLsmg_set_color(0);
	SLsmg_fill_region(y, 0, 3, SLtt_Screen_Cols, ' ');
	SLsmg_refresh();
	pthread_mutex_unlock(&ui__lock);
}