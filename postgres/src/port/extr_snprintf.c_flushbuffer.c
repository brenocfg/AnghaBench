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
struct TYPE_3__ {size_t bufptr; size_t bufstart; int failed; size_t nchars; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ PrintfTarget ;

/* Variables and functions */
 size_t fwrite (size_t,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flushbuffer(PrintfTarget *target)
{
	size_t		nc = target->bufptr - target->bufstart;

	/*
	 * Don't write anything if we already failed; this is to ensure we
	 * preserve the original failure's errno.
	 */
	if (!target->failed && nc > 0)
	{
		size_t		written;

		written = fwrite(target->bufstart, 1, nc, target->stream);
		target->nchars += written;
		if (written != nc)
			target->failed = true;
	}
	target->bufptr = target->bufstart;
}