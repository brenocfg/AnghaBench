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

/* Variables and functions */
 unsigned char CSI ; 
 scalar_t__ Columns ; 
 scalar_t__ Rows ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  out_char (unsigned char) ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  out_num (long) ; 
 int /*<<< orphan*/  size_set ; 
 scalar_t__ term_console ; 

void
mch_set_shellsize()
{
    if (term_console)
    {
	size_set = TRUE;
	out_char(CSI);
	out_num((long)Rows);
	out_char('t');
	out_char(CSI);
	out_num((long)Columns);
	out_char('u');
	out_flush();
    }
}