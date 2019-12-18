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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int Columns ; 
 int /*<<< orphan*/  OUT_STR_NF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Rows ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  screen_start () ; 
 int /*<<< orphan*/  set_tty (int /*<<< orphan*/ ,int) ; 

void
mch_set_shellsize(void)
{
    set_tty(Rows, Columns);
    switch (Columns)
    {
	case 132:	OUT_STR_NF((char_u *)"\033[?3h\033>");	break;
	case 80:	OUT_STR_NF((char_u *)"\033[?3l\033>");	break;
	default:	break;
    }
    out_flush();
    screen_start();
}