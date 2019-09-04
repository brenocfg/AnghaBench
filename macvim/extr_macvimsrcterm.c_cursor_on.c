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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  T_VE ; 
 scalar_t__ cursor_is_off ; 
 int /*<<< orphan*/  out_str (int /*<<< orphan*/ ) ; 

void
cursor_on()
{
    if (cursor_is_off)
    {
	out_str(T_VE);
	cursor_is_off = FALSE;
    }
}