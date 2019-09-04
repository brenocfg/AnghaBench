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
 unsigned long O_APPEND ; 
 unsigned long O_ASYNC ; 
 unsigned long O_CLOEXEC ; 
 unsigned long O_CREAT ; 
 unsigned long O_DIRECT ; 
 unsigned long O_DIRECTORY ; 
 unsigned long O_EXCL ; 
 unsigned long O_LARGEFILE ; 
 unsigned long O_NOATIME ; 
 unsigned long O_NOCTTY ; 
 unsigned long O_NOFOLLOW ; 
 unsigned long O_RDWR ; 
 unsigned long O_SYNC ; 
 unsigned long O_TMPFILE ; 
 unsigned long O_TRUNC ; 
 unsigned long O_WRONLY ; 
 size_t scnprintf (char*,size_t,char*,...) ; 

size_t open__scnprintf_flags(unsigned long flags, char *bf, size_t size)
{
	int printed = 0;

	if (flags == 0)
		return scnprintf(bf, size, "RDONLY");
#define	P_FLAG(n) \
	if (flags & O_##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		flags &= ~O_##n; \
	}

	P_FLAG(RDWR);
	P_FLAG(APPEND);
	P_FLAG(ASYNC);
	P_FLAG(CLOEXEC);
	P_FLAG(CREAT);
	P_FLAG(DIRECT);
	P_FLAG(DIRECTORY);
	P_FLAG(EXCL);
	P_FLAG(LARGEFILE);
	P_FLAG(NOFOLLOW);
	P_FLAG(TMPFILE);
	P_FLAG(NOATIME);
	P_FLAG(NOCTTY);
#ifdef O_NONBLOCK
	P_FLAG(NONBLOCK);
#elif O_NDELAY
	P_FLAG(NDELAY);
#endif
#ifdef O_PATH
	P_FLAG(PATH);
#endif
#ifdef O_DSYNC
	if ((flags & O_SYNC) == O_SYNC)
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", "SYNC");
	else {
		P_FLAG(DSYNC);
	}
#else
	P_FLAG(SYNC);
#endif
	P_FLAG(TRUNC);
	P_FLAG(WRONLY);
#undef P_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", flags);

	return printed;
}