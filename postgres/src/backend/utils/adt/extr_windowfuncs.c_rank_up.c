#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int rank; } ;
typedef  TYPE_1__ rank_context ;
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  WindowObject ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ WinGetCurrentPosition (int /*<<< orphan*/ ) ; 
 scalar_t__ WinGetPartitionLocalMemory (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WinRowsArePeers (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WinSetMarkPosition (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
rank_up(WindowObject winobj)
{
	bool		up = false;		/* should rank increase? */
	int64		curpos = WinGetCurrentPosition(winobj);
	rank_context *context;

	context = (rank_context *)
		WinGetPartitionLocalMemory(winobj, sizeof(rank_context));

	if (context->rank == 0)
	{
		/* first call: rank of first row is always 1 */
		Assert(curpos == 0);
		context->rank = 1;
	}
	else
	{
		Assert(curpos > 0);
		/* do current and prior tuples match by ORDER BY clause? */
		if (!WinRowsArePeers(winobj, curpos - 1, curpos))
			up = true;
	}

	/* We can advance the mark, but only *after* access to prior row */
	WinSetMarkPosition(winobj, curpos);

	return up;
}