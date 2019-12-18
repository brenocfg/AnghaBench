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
 scalar_t__ EVENT_CURSORHOLD ; 
 scalar_t__ EVENT_CURSORHOLDI ; 
 scalar_t__ NORMAL_BUSY ; 
 int /*<<< orphan*/ ** first_autopat ; 
 scalar_t__ get_real_state () ; 

int
has_cursorhold()
{
    return (first_autopat[(int)(get_real_state() == NORMAL_BUSY
			    ? EVENT_CURSORHOLD : EVENT_CURSORHOLDI)] != NULL);
}