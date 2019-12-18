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
 char* strerror (int) ; 
 char* strerror_r (int,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static char *
gnuish_strerror_r(int errnum, char *buf, size_t buflen)
{
#ifdef HAVE_STRERROR_R
#ifdef STRERROR_R_INT
	/* POSIX API */
	if (strerror_r(errnum, buf, buflen) == 0)
		return buf;
	return NULL;				/* let caller deal with failure */
#else
	/* GNU API */
	return strerror_r(errnum, buf, buflen);
#endif
#else							/* !HAVE_STRERROR_R */
	char	   *sbuf = strerror(errnum);

	if (sbuf == NULL)			/* can this still happen anywhere? */
		return NULL;
	/* To minimize thread-unsafety hazard, copy into caller's buffer */
	strlcpy(buf, sbuf, buflen);
	return buf;
#endif
}