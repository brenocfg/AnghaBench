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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closelog () ; 

__attribute__((used)) static void
close_fds_except(int keep)
{
    int i;
    closelog();
    for (i = 3; i <= 100; ++i)
    {
        if (i != keep)
        {
            close(i);
        }
    }
}