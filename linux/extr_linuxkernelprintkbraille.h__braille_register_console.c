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
struct console_cmdline {int dummy; } ;
struct console {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
_braille_register_console(struct console *console, struct console_cmdline *c)
{
	return 0;
}