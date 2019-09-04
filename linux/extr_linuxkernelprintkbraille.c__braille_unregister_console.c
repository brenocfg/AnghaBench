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
struct console {int flags; } ;

/* Variables and functions */
 int CON_BRL ; 
 int braille_unregister_console (struct console*) ; 

int
_braille_unregister_console(struct console *console)
{
	if (console->flags & CON_BRL)
		return braille_unregister_console(console);

	return 0;
}