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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int MaxAllocSize ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

size_t
pvsnprintf(char *buf, size_t len, const char *fmt, va_list args)
{
	int			nprinted;

	nprinted = vsnprintf(buf, len, fmt, args);

	/* We assume failure means the fmt is bogus, hence hard failure is OK */
	if (unlikely(nprinted < 0))
	{
#ifndef FRONTEND
		elog(ERROR, "vsnprintf failed: %m with format string \"%s\"", fmt);
#else
		fprintf(stderr, "vsnprintf failed: %s with format string \"%s\"\n",
				strerror(errno), fmt);
		exit(EXIT_FAILURE);
#endif
	}

	if ((size_t) nprinted < len)
	{
		/* Success.  Note nprinted does not include trailing null. */
		return (size_t) nprinted;
	}

	/*
	 * We assume a C99-compliant vsnprintf, so believe its estimate of the
	 * required space, and add one for the trailing null.  (If it's wrong, the
	 * logic will still work, but we may loop multiple times.)
	 *
	 * Choke if the required space would exceed MaxAllocSize.  Note we use
	 * this palloc-oriented overflow limit even when in frontend.
	 */
	if (unlikely((size_t) nprinted > MaxAllocSize - 1))
	{
#ifndef FRONTEND
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("out of memory")));
#else
		fprintf(stderr, _("out of memory\n"));
		exit(EXIT_FAILURE);
#endif
	}

	return nprinted + 1;
}