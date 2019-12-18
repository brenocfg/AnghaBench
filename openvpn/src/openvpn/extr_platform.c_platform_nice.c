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
 int M_ERRNO ; 
 int M_INFO ; 
 int M_WARN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  msg (int,char*,int) ; 
 scalar_t__ nice (int) ; 

void
platform_nice(int niceval)
{
    if (niceval)
    {
#ifdef HAVE_NICE
        errno = 0;
        if (nice(niceval) < 0 && errno != 0)
        {
            msg(M_WARN | M_ERRNO, "WARNING: nice %d failed", niceval);
        }
        else
        {
            msg(M_INFO, "nice %d succeeded", niceval);
        }
#else  /* ifdef HAVE_NICE */
        msg(M_WARN, "WARNING: nice %d failed (function not implemented)", niceval);
#endif
    }
}