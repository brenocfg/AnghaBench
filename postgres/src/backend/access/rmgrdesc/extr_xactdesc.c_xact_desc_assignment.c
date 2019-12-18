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
struct TYPE_3__ {int nsubxacts; int /*<<< orphan*/ * xsub; } ;
typedef  TYPE_1__ xl_xact_assignment ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
xact_desc_assignment(StringInfo buf, xl_xact_assignment *xlrec)
{
	int			i;

	appendStringInfoString(buf, "subxacts:");

	for (i = 0; i < xlrec->nsubxacts; i++)
		appendStringInfo(buf, " %u", xlrec->xsub[i]);
}