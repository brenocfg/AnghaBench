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
struct TYPE_4__ {int /*<<< orphan*/ * bufptr; int /*<<< orphan*/  nchars; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * bufend; } ;
typedef  TYPE_1__ PrintfTarget ;

/* Variables and functions */
 int /*<<< orphan*/  flushbuffer (TYPE_1__*) ; 

__attribute__((used)) static void
dopr_outch(int c, PrintfTarget *target)
{
	if (target->bufend != NULL && target->bufptr >= target->bufend)
	{
		/* buffer full, can we dump to stream? */
		if (target->stream == NULL)
		{
			target->nchars++;	/* no, lose the data */
			return;
		}
		flushbuffer(target);
	}
	*(target->bufptr++) = c;
}