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
 scalar_t__ GetCurrentProcessId () ; 
 scalar_t__ getpid () ; 

unsigned int
platform_getpid(void)
{
#ifdef _WIN32
    return (unsigned int) GetCurrentProcessId();
#else
#ifdef HAVE_GETPID
    return (unsigned int) getpid();
#else
    return 0;
#endif
#endif
}