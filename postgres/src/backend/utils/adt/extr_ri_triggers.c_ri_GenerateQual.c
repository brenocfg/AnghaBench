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

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  generate_operator_clause (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ri_GenerateQual(StringInfo buf,
				const char *sep,
				const char *leftop, Oid leftoptype,
				Oid opoid,
				const char *rightop, Oid rightoptype)
{
	appendStringInfo(buf, " %s ", sep);
	generate_operator_clause(buf, leftop, leftoptype, opoid,
							 rightop, rightoptype);
}