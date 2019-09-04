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
struct tty_driver {int name_base; scalar_t__ subtype; char* name; } ;

/* Variables and functions */
 scalar_t__ PTY_TYPE_SLAVE ; 
 int* ptychar ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int) ; 

__attribute__((used)) static void pty_line_name(struct tty_driver *driver, int index, char *p)
{
	int i = index + driver->name_base;
	/* ->name is initialized to "ttyp", but "tty" is expected */
	sprintf(p, "%s%c%x",
		driver->subtype == PTY_TYPE_SLAVE ? "tty" : driver->name,
		ptychar[i >> 4 & 0xf], i & 0xf);
}