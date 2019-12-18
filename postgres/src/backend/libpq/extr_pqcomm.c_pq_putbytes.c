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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoingCopyOut ; 
 int PqCommBusy ; 
 int internal_putbytes (char const*,size_t) ; 

int
pq_putbytes(const char *s, size_t len)
{
	int			res;

	/* Should only be called by old-style COPY OUT */
	Assert(DoingCopyOut);
	/* No-op if reentrant call */
	if (PqCommBusy)
		return 0;
	PqCommBusy = true;
	res = internal_putbytes(s, len);
	PqCommBusy = false;
	return res;
}