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
struct debuginfo {scalar_t__ dwfl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwfl_end (scalar_t__) ; 
 int /*<<< orphan*/  free (struct debuginfo*) ; 

void debuginfo__delete(struct debuginfo *dbg)
{
	if (dbg) {
		if (dbg->dwfl)
			dwfl_end(dbg->dwfl);
		free(dbg);
	}
}