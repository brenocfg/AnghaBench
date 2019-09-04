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
 long BIOSTICK ; 
 int /*<<< orphan*/  WaitForChar (long) ; 
 long biostime (int /*<<< orphan*/ ,long) ; 

void
mch_delay(
    long	msec,
    int		ignoreinput)
{
    long	starttime;

    if (ignoreinput)
    {
	/*
	 * We busy-wait here.  Unfortunately, delay() and usleep() have been
	 * reported to give problems with the original Windows 95.  This is
	 * fixed in service pack 1, but not everybody installed that.
	 */
	starttime = biostime(0, 0L);
	while (biostime(0, 0L) < starttime + msec / BIOSTICK)
	    ;
    }
    else
	WaitForChar(msec);
}