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

void os_set_thread_name(const char *name)
{
#if defined(__APPLE__)
	pthread_setname_np(name);
#elif defined(__FreeBSD__)
	pthread_set_name_np(pthread_self(), name);
#elif defined(__GLIBC__) && !defined(__MINGW32__)
	if (strlen(name) <= 15) {
		pthread_setname_np(pthread_self(), name);
	} else {
		char *thread_name = bstrdup_n(name, 15);
		pthread_setname_np(pthread_self(), thread_name);
		bfree(thread_name);
	}
#endif
}