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
struct TYPE_3__ {int /*<<< orphan*/  constbyval; int /*<<< orphan*/  constlen; int /*<<< orphan*/  constvalue; scalar_t__ constisnull; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ Const ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  constbyval ; 
 int /*<<< orphan*/  constcollid ; 
 int /*<<< orphan*/  constisnull ; 
 int /*<<< orphan*/  constlen ; 
 int /*<<< orphan*/  consttype ; 
 int /*<<< orphan*/  consttypmod ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  outDatum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_outConst(StringInfo str, const Const *node)
{
	WRITE_NODE_TYPE("CONST");

	WRITE_OID_FIELD(consttype);
	WRITE_INT_FIELD(consttypmod);
	WRITE_OID_FIELD(constcollid);
	WRITE_INT_FIELD(constlen);
	WRITE_BOOL_FIELD(constbyval);
	WRITE_BOOL_FIELD(constisnull);
	WRITE_LOCATION_FIELD(location);

	appendStringInfoString(str, " :constvalue ");
	if (node->constisnull)
		appendStringInfoString(str, "<>");
	else
		outDatum(str, node->constvalue, node->constlen, node->constbyval);
}