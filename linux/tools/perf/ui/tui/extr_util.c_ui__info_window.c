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
 int /*<<< orphan*/  SLsmg_refresh () ; 
 int /*<<< orphan*/  __ui__info_window (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui__lock ; 

void ui__info_window(const char *title, const char *text)
{
	pthread_mutex_lock(&ui__lock);
	__ui__info_window(title, text, NULL);
	SLsmg_refresh();
	pthread_mutex_unlock(&ui__lock);
}