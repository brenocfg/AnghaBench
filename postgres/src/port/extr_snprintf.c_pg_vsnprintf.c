#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {char* bufstart; char* bufptr; char* bufend; int nchars; int failed; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ PrintfTarget ;

/* Variables and functions */
 int /*<<< orphan*/  dopr (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

int
pg_vsnprintf(char *str, size_t count, const char *fmt, va_list args)
{
	PrintfTarget target;
	char		onebyte[1];

	/*
	 * C99 allows the case str == NULL when count == 0.  Rather than
	 * special-casing this situation further down, we substitute a one-byte
	 * local buffer.  Callers cannot tell, since the function result doesn't
	 * depend on count.
	 */
	if (count == 0)
	{
		str = onebyte;
		count = 1;
	}
	target.bufstart = target.bufptr = str;
	target.bufend = str + count - 1;
	target.stream = NULL;
	target.nchars = 0;
	target.failed = false;
	dopr(&target, fmt, args);
	*(target.bufptr) = '\0';
	return target.failed ? -1 : (target.bufptr - target.bufstart
								 + target.nchars);
}