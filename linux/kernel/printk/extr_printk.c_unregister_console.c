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
struct console {int flags; struct console* next; int /*<<< orphan*/  index; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CON_BOOT ; 
 int CON_CONSDEV ; 
 int CON_ENABLED ; 
 int CON_EXTENDED ; 
 int _braille_unregister_console (struct console*) ; 
 struct console* console_drivers ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_sysfs_notify () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  nr_ext_console_drivers ; 
 int /*<<< orphan*/  pr_info (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int unregister_console(struct console *console)
{
        struct console *a, *b;
	int res;

	pr_info("%sconsole [%s%d] disabled\n",
		(console->flags & CON_BOOT) ? "boot" : "" ,
		console->name, console->index);

	res = _braille_unregister_console(console);
	if (res)
		return res;

	res = 1;
	console_lock();
	if (console_drivers == console) {
		console_drivers=console->next;
		res = 0;
	} else if (console_drivers) {
		for (a=console_drivers->next, b=console_drivers ;
		     a; b=a, a=b->next) {
			if (a == console) {
				b->next = a->next;
				res = 0;
				break;
			}
		}
	}

	if (!res && (console->flags & CON_EXTENDED))
		nr_ext_console_drivers--;

	/*
	 * If this isn't the last console and it has CON_CONSDEV set, we
	 * need to set it on the next preferred console.
	 */
	if (console_drivers != NULL && console->flags & CON_CONSDEV)
		console_drivers->flags |= CON_CONSDEV;

	console->flags &= ~CON_ENABLED;
	console_unlock();
	console_sysfs_notify();
	return res;
}