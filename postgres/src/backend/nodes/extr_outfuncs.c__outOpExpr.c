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
typedef  int /*<<< orphan*/  OpExpr ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  inputcollid ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  opcollid ; 
 int /*<<< orphan*/  opfuncid ; 
 int /*<<< orphan*/  opno ; 
 int /*<<< orphan*/  opresulttype ; 
 int /*<<< orphan*/  opretset ; 

__attribute__((used)) static void
_outOpExpr(StringInfo str, const OpExpr *node)
{
	WRITE_NODE_TYPE("OPEXPR");

	WRITE_OID_FIELD(opno);
	WRITE_OID_FIELD(opfuncid);
	WRITE_OID_FIELD(opresulttype);
	WRITE_BOOL_FIELD(opretset);
	WRITE_OID_FIELD(opcollid);
	WRITE_OID_FIELD(inputcollid);
	WRITE_NODE_FIELD(args);
	WRITE_LOCATION_FIELD(location);
}