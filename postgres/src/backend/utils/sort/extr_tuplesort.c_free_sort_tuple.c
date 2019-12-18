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
typedef  int /*<<< orphan*/  Tuplesortstate ;
struct TYPE_3__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ SortTuple ;

/* Variables and functions */
 int /*<<< orphan*/  FREEMEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_sort_tuple(Tuplesortstate *state, SortTuple *stup)
{
	FREEMEM(state, GetMemoryChunkSpace(stup->tuple));
	pfree(stup->tuple);
}