#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct console {size_t index; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int goldfish_tty_line_count ; 
 TYPE_1__* goldfish_ttys ; 

__attribute__((used)) static int goldfish_tty_console_setup(struct console *co, char *options)
{
	if ((unsigned)co->index >= goldfish_tty_line_count)
		return -ENODEV;
	if (!goldfish_ttys[co->index].base)
		return -ENODEV;
	return 0;
}