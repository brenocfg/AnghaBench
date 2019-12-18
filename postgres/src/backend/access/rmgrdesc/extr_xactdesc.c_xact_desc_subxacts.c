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
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
xact_desc_subxacts(StringInfo buf, int nsubxacts, TransactionId *subxacts)
{
	int		i;

	if (nsubxacts > 0)
	{
		appendStringInfoString(buf, "; subxacts:");
		for (i = 0; i < nsubxacts; i++)
			appendStringInfo(buf, " %u", subxacts[i]);
	}
}