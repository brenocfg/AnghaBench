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
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 int M_ERRNO ; 
 int M_INFO ; 
 int M_WARN ; 
 scalar_t__ mlockall (int) ; 
 int /*<<< orphan*/  msg (int,char*) ; 

void
platform_mlockall(bool print_msg)
{
#ifdef HAVE_MLOCKALL
    if (mlockall(MCL_CURRENT | MCL_FUTURE))
    {
        msg(M_WARN | M_ERRNO, "WARNING: mlockall call failed");
    }
    else if (print_msg)
    {
        msg(M_INFO, "mlockall call succeeded");
    }
#else  /* ifdef HAVE_MLOCKALL */
    msg(M_WARN, "WARNING: mlockall call failed (function not implemented)");
#endif
}