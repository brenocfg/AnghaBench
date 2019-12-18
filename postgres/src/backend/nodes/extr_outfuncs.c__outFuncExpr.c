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
typedef  int /*<<< orphan*/  FuncExpr ;

/* Variables and functions */
 int /*<<< orphan*/  CoercionForm ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  funccollid ; 
 int /*<<< orphan*/  funcformat ; 
 int /*<<< orphan*/  funcid ; 
 int /*<<< orphan*/  funcresulttype ; 
 int /*<<< orphan*/  funcretset ; 
 int /*<<< orphan*/  funcvariadic ; 
 int /*<<< orphan*/  inputcollid ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static void
_outFuncExpr(StringInfo str, const FuncExpr *node)
{
	WRITE_NODE_TYPE("FUNCEXPR");

	WRITE_OID_FIELD(funcid);
	WRITE_OID_FIELD(funcresulttype);
	WRITE_BOOL_FIELD(funcretset);
	WRITE_BOOL_FIELD(funcvariadic);
	WRITE_ENUM_FIELD(funcformat, CoercionForm);
	WRITE_OID_FIELD(funccollid);
	WRITE_OID_FIELD(inputcollid);
	WRITE_NODE_FIELD(args);
	WRITE_LOCATION_FIELD(location);
}