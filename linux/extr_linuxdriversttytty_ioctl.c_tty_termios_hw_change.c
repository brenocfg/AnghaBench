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
struct ktermios {scalar_t__ c_ispeed; scalar_t__ c_ospeed; int c_cflag; } ;

/* Variables and functions */
 int CLOCAL ; 
 int CREAD ; 
 int HUPCL ; 

int tty_termios_hw_change(const struct ktermios *a, const struct ktermios *b)
{
	if (a->c_ispeed != b->c_ispeed || a->c_ospeed != b->c_ospeed)
		return 1;
	if ((a->c_cflag ^ b->c_cflag) & ~(HUPCL | CREAD | CLOCAL))
		return 1;
	return 0;
}