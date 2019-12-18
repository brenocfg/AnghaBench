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
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgmname_syslog ; 
 int use_syslog ; 

void
close_syslog(void)
{
#if SYSLOG_CAPABILITY
    if (use_syslog)
    {
        closelog();
        use_syslog = false;
        if (pgmname_syslog)
        {
            free(pgmname_syslog);
            pgmname_syslog = NULL;
        }
    }
#endif
}