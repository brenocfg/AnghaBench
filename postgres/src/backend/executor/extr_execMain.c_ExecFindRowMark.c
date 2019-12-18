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
struct TYPE_3__ {int es_range_table_size; int /*<<< orphan*/ ** es_rowmarks; } ;
typedef  int Index ;
typedef  int /*<<< orphan*/  ExecRowMark ;
typedef  TYPE_1__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

ExecRowMark *
ExecFindRowMark(EState *estate, Index rti, bool missing_ok)
{
	if (rti > 0 && rti <= estate->es_range_table_size &&
		estate->es_rowmarks != NULL)
	{
		ExecRowMark *erm = estate->es_rowmarks[rti - 1];

		if (erm)
			return erm;
	}
	if (!missing_ok)
		elog(ERROR, "failed to find ExecRowMark for rangetable index %u", rti);
	return NULL;
}