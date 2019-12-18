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
struct ui_browser {int /*<<< orphan*/  helpline; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui__lock ; 
 int /*<<< orphan*/  ui_helpline__pop () ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void ui_browser__hide(struct ui_browser *browser)
{
	pthread_mutex_lock(&ui__lock);
	ui_helpline__pop();
	zfree(&browser->helpline);
	pthread_mutex_unlock(&ui__lock);
}