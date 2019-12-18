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
 char* strsignal (int) ; 

const char *
pg_strsignal(int signum)
{
	const char *result;

	/*
	 * If we have strsignal(3), use that --- but check its result for NULL.
	 */
#ifdef HAVE_STRSIGNAL
	result = strsignal(signum);
	if (result == NULL)
		result = "unrecognized signal";
#else

	/*
	 * We used to have code here to try to use sys_siglist[] if available.
	 * However, it seems that all platforms with sys_siglist[] have also had
	 * strsignal() for many years now, so that was just a waste of code.
	 */
	result = "(signal names not available on this platform)";
#endif

	return result;
}