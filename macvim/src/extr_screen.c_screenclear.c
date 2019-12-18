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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  check_for_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screenalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screenclear2 () ; 

void
screenclear()
{
    check_for_delay(FALSE);
    screenalloc(FALSE);	    /* allocate screen buffers if size changed */
    screenclear2();	    /* clear the screen */
}