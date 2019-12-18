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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int errno ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,size_t,struct passwd**) ; 

int
pqGetpwuid(uid_t uid, struct passwd *resultbuf, char *buffer,
		   size_t buflen, struct passwd **result)
{
#if defined(FRONTEND) && defined(ENABLE_THREAD_SAFETY) && defined(HAVE_GETPWUID_R)
	return getpwuid_r(uid, resultbuf, buffer, buflen, result);
#else
	/* no getpwuid_r() available, just use getpwuid() */
	errno = 0;
	*result = getpwuid(uid);
	/* paranoia: ensure we return zero on success */
	return (*result == NULL) ? errno : 0;
#endif
}