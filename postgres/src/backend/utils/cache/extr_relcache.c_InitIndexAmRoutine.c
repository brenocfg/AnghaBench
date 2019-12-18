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
struct TYPE_3__ {int /*<<< orphan*/ * rd_indam; int /*<<< orphan*/  rd_indexcxt; int /*<<< orphan*/  rd_amhandler; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  IndexAmRoutine ;

/* Variables and functions */
 int /*<<< orphan*/ * GetIndexAmRoutine (int /*<<< orphan*/ ) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
InitIndexAmRoutine(Relation relation)
{
	IndexAmRoutine *cached,
			   *tmp;

	/*
	 * Call the amhandler in current, short-lived memory context, just in case
	 * it leaks anything (it probably won't, but let's be paranoid).
	 */
	tmp = GetIndexAmRoutine(relation->rd_amhandler);

	/* OK, now transfer the data into relation's rd_indexcxt. */
	cached = (IndexAmRoutine *) MemoryContextAlloc(relation->rd_indexcxt,
												   sizeof(IndexAmRoutine));
	memcpy(cached, tmp, sizeof(IndexAmRoutine));
	relation->rd_indam = cached;

	pfree(tmp);
}