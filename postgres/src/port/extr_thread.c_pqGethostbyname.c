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
struct hostent {int dummy; } ;

/* Variables and functions */
 struct hostent* gethostbyname (char const*) ; 
 struct hostent* gethostbyname_r (char const*,struct hostent*,char*,size_t,int*) ; 
 int h_errno ; 

int
pqGethostbyname(const char *name,
				struct hostent *resultbuf,
				char *buffer, size_t buflen,
				struct hostent **result,
				int *herrno)
{
#if defined(FRONTEND) && defined(ENABLE_THREAD_SAFETY) && defined(HAVE_GETHOSTBYNAME_R)

	/*
	 * broken (well early POSIX draft) gethostbyname_r() which returns 'struct
	 * hostent *'
	 */
	*result = gethostbyname_r(name, resultbuf, buffer, buflen, herrno);
	return (*result == NULL) ? -1 : 0;
#else

	/* no gethostbyname_r(), just use gethostbyname() */
	*result = gethostbyname(name);

	if (*result != NULL)
		*herrno = h_errno;

	if (*result != NULL)
		return 0;
	else
		return -1;
#endif
}