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
 char* _ (char*) ; 
 char* get_errno_symbol (int) ; 
 char* gnuish_strerror_r (int,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 char* win32_socket_strerror (int,char*,size_t) ; 

char *
pg_strerror_r(int errnum, char *buf, size_t buflen)
{
	char	   *str;

	/* If it's a Windows Winsock error, that needs special handling */
#ifdef WIN32
	/* Winsock error code range, per WinError.h */
	if (errnum >= 10000 && errnum <= 11999)
		return win32_socket_strerror(errnum, buf, buflen);
#endif

	/* Try the platform's strerror_r(), or maybe just strerror() */
	str = gnuish_strerror_r(errnum, buf, buflen);

	/*
	 * Some strerror()s return an empty string for out-of-range errno.  This
	 * is ANSI C spec compliant, but not exactly useful.  Also, we may get
	 * back strings of question marks if libc cannot transcode the message to
	 * the codeset specified by LC_CTYPE.  If we get nothing useful, first try
	 * get_errno_symbol(), and if that fails, print the numeric errno.
	 */
	if (str == NULL || *str == '\0' || *str == '?')
		str = get_errno_symbol(errnum);

	if (str == NULL)
	{
		snprintf(buf, buflen, _("operating system error %d"), errnum);
		str = buf;
	}

	return str;
}