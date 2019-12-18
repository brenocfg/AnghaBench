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
 scalar_t__ gtk_init_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_ui_progress__init () ; 
 int /*<<< orphan*/  perf_error__register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_gtk__init_helpline () ; 
 int /*<<< orphan*/  perf_gtk__init_hpp () ; 
 int /*<<< orphan*/  perf_gtk_eops ; 

int perf_gtk__init(void)
{
	perf_error__register(&perf_gtk_eops);
	perf_gtk__init_helpline();
	gtk_ui_progress__init();
	perf_gtk__init_hpp();

	return gtk_init_check(NULL, NULL) ? 0 : -1;
}