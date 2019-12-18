#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tms {int /*<<< orphan*/  tms_cstime; int /*<<< orphan*/  tms_cutime; int /*<<< orphan*/  tms_stime; int /*<<< orphan*/  tms_utime; } ;
struct TYPE_6__ {long tv_sec; long tv_usec; } ;
struct TYPE_5__ {long tv_sec; long tv_usec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;
typedef  int /*<<< orphan*/  clock_t ;
struct TYPE_7__ {long QuadPart; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int CLK_TCK ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetProcessTimes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  RUSAGE_CHILDREN 129 
#define  RUSAGE_SELF 128 
 void* TICK_TO_SEC (int /*<<< orphan*/ ,int) ; 
 void* TICK_TO_USEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _dosmaperr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct rusage*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ times (struct tms*) ; 

int
getrusage(int who, struct rusage *rusage)
{
#ifdef WIN32
	FILETIME	starttime;
	FILETIME	exittime;
	FILETIME	kerneltime;
	FILETIME	usertime;
	ULARGE_INTEGER li;

	if (who != RUSAGE_SELF)
	{
		/* Only RUSAGE_SELF is supported in this implementation for now */
		errno = EINVAL;
		return -1;
	}

	if (rusage == (struct rusage *) NULL)
	{
		errno = EFAULT;
		return -1;
	}
	memset(rusage, 0, sizeof(struct rusage));
	if (GetProcessTimes(GetCurrentProcess(),
						&starttime, &exittime, &kerneltime, &usertime) == 0)
	{
		_dosmaperr(GetLastError());
		return -1;
	}

	/* Convert FILETIMEs (0.1 us) to struct timeval */
	memcpy(&li, &kerneltime, sizeof(FILETIME));
	li.QuadPart /= 10L;			/* Convert to microseconds */
	rusage->ru_stime.tv_sec = li.QuadPart / 1000000L;
	rusage->ru_stime.tv_usec = li.QuadPart % 1000000L;

	memcpy(&li, &usertime, sizeof(FILETIME));
	li.QuadPart /= 10L;			/* Convert to microseconds */
	rusage->ru_utime.tv_sec = li.QuadPart / 1000000L;
	rusage->ru_utime.tv_usec = li.QuadPart % 1000000L;
#else							/* all but WIN32 */

	struct tms	tms;
	int			tick_rate = CLK_TCK;	/* ticks per second */
	clock_t		u,
				s;

	if (rusage == (struct rusage *) NULL)
	{
		errno = EFAULT;
		return -1;
	}
	if (times(&tms) < 0)
	{
		/* errno set by times */
		return -1;
	}
	switch (who)
	{
		case RUSAGE_SELF:
			u = tms.tms_utime;
			s = tms.tms_stime;
			break;
		case RUSAGE_CHILDREN:
			u = tms.tms_cutime;
			s = tms.tms_cstime;
			break;
		default:
			errno = EINVAL;
			return -1;
	}
#define TICK_TO_SEC(T, RATE)	((T)/(RATE))
#define TICK_TO_USEC(T,RATE)	(((T)%(RATE)*1000000)/RATE)
	rusage->ru_utime.tv_sec = TICK_TO_SEC(u, tick_rate);
	rusage->ru_utime.tv_usec = TICK_TO_USEC(u, tick_rate);
	rusage->ru_stime.tv_sec = TICK_TO_SEC(s, tick_rate);
	rusage->ru_stime.tv_usec = TICK_TO_USEC(u, tick_rate);
#endif							/* WIN32 */

	return 0;
}