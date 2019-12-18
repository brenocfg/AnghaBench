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
typedef  int /*<<< orphan*/  tv32 ;
typedef  int /*<<< orphan*/  tv ;
struct old_timeval32 {long member_0; long member_1; } ;
struct __kernel_sock_timeval {long tv_sec; long tv_usec; } ;
struct __kernel_old_timeval {long tv_sec; long tv_usec; } ;
typedef  int /*<<< orphan*/  old_tv ;

/* Variables and functions */
 int /*<<< orphan*/  COMPAT_USE_64BIT_TIME ; 
 long HZ ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 long USEC_PER_SEC ; 
 scalar_t__ in_compat_syscall () ; 

__attribute__((used)) static int sock_get_timeout(long timeo, void *optval, bool old_timeval)
{
	struct __kernel_sock_timeval tv;
	int size;

	if (timeo == MAX_SCHEDULE_TIMEOUT) {
		tv.tv_sec = 0;
		tv.tv_usec = 0;
	} else {
		tv.tv_sec = timeo / HZ;
		tv.tv_usec = ((timeo % HZ) * USEC_PER_SEC) / HZ;
	}

	if (old_timeval && in_compat_syscall() && !COMPAT_USE_64BIT_TIME) {
		struct old_timeval32 tv32 = { tv.tv_sec, tv.tv_usec };
		*(struct old_timeval32 *)optval = tv32;
		return sizeof(tv32);
	}

	if (old_timeval) {
		struct __kernel_old_timeval old_tv;
		old_tv.tv_sec = tv.tv_sec;
		old_tv.tv_usec = tv.tv_usec;
		*(struct __kernel_old_timeval *)optval = old_tv;
		size = sizeof(old_tv);
	} else {
		*(struct __kernel_sock_timeval *)optval = tv;
		size = sizeof(tv);
	}

	return size;
}