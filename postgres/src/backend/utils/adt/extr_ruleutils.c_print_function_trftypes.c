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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int get_func_trftypes (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
print_function_trftypes(StringInfo buf, HeapTuple proctup)
{
	Oid		   *trftypes;
	int			ntypes;

	ntypes = get_func_trftypes(proctup, &trftypes);
	if (ntypes > 0)
	{
		int			i;

		appendStringInfoString(buf, "\n TRANSFORM ");
		for (i = 0; i < ntypes; i++)
		{
			if (i != 0)
				appendStringInfoString(buf, ", ");
			appendStringInfo(buf, "FOR TYPE %s", format_type_be(trftypes[i]));
		}
	}
}