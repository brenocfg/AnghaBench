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
struct console {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_ENABLED ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 

void console_stop(struct console *console)
{
	console_lock();
	console->flags &= ~CON_ENABLED;
	console_unlock();
}