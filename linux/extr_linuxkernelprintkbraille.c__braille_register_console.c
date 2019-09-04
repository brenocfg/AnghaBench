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
struct console_cmdline {scalar_t__ brl_options; int /*<<< orphan*/  options; int /*<<< orphan*/  index; } ;
struct console {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_BRL ; 
 int braille_register_console (struct console*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
_braille_register_console(struct console *console, struct console_cmdline *c)
{
	int rtn = 0;

	if (c->brl_options) {
		console->flags |= CON_BRL;
		rtn = braille_register_console(console, c->index, c->options,
					       c->brl_options);
	}

	return rtn;
}