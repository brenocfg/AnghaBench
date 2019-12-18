#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {char* bufstart; char* bufptr; char* bufend; int nchars; int failed; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ PrintfTarget ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dopr (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  flushbuffer (TYPE_1__*) ; 

int
pg_vfprintf(FILE *stream, const char *fmt, va_list args)
{
	PrintfTarget target;
	char		buffer[1024];	/* size is arbitrary */

	if (stream == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	target.bufstart = target.bufptr = buffer;
	target.bufend = buffer + sizeof(buffer);	/* use the whole buffer */
	target.stream = stream;
	target.nchars = 0;
	target.failed = false;
	dopr(&target, fmt, args);
	/* dump any remaining buffer contents */
	flushbuffer(&target);
	return target.failed ? -1 : target.nchars;
}