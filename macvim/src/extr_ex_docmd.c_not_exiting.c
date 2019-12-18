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
 int /*<<< orphan*/  TMODE_RAW ; 
 int /*<<< orphan*/  exiting ; 
 int /*<<< orphan*/  settmode (int /*<<< orphan*/ ) ; 

void
not_exiting()
{
    exiting = FALSE;
    settmode(TMODE_RAW);
}