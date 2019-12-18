#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* mergeactive; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  SortTuple ;

/* Variables and functions */
 int /*<<< orphan*/  READTUP (TYPE_1__*,int /*<<< orphan*/ *,int,unsigned int) ; 
 unsigned int getlen (TYPE_1__*,int,int) ; 

__attribute__((used)) static bool
mergereadnext(Tuplesortstate *state, int srcTape, SortTuple *stup)
{
	unsigned int tuplen;

	if (!state->mergeactive[srcTape])
		return false;			/* tape's run is already exhausted */

	/* read next tuple, if any */
	if ((tuplen = getlen(state, srcTape, true)) == 0)
	{
		state->mergeactive[srcTape] = false;
		return false;
	}
	READTUP(state, stup, srcTape, tuplen);

	return true;
}