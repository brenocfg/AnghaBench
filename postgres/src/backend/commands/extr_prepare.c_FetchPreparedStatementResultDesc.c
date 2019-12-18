#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_5__ {TYPE_1__* plansource; } ;
struct TYPE_4__ {scalar_t__ resultDesc; int /*<<< orphan*/  fixed_result; } ;
typedef  TYPE_2__ PreparedStatement ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateTupleDescCopy (scalar_t__) ; 

TupleDesc
FetchPreparedStatementResultDesc(PreparedStatement *stmt)
{
	/*
	 * Since we don't allow prepared statements' result tupdescs to change,
	 * there's no need to worry about revalidating the cached plan here.
	 */
	Assert(stmt->plansource->fixed_result);
	if (stmt->plansource->resultDesc)
		return CreateTupleDescCopy(stmt->plansource->resultDesc);
	else
		return NULL;
}