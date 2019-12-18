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
typedef  int /*<<< orphan*/  CommonTableExpr ;

/* Variables and functions */
 int /*<<< orphan*/  CTEMaterialize ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aliascolnames ; 
 int /*<<< orphan*/  ctecolcollations ; 
 int /*<<< orphan*/  ctecolnames ; 
 int /*<<< orphan*/  ctecoltypes ; 
 int /*<<< orphan*/  ctecoltypmods ; 
 int /*<<< orphan*/  ctematerialized ; 
 int /*<<< orphan*/  ctename ; 
 int /*<<< orphan*/  ctequery ; 
 int /*<<< orphan*/  cterecursive ; 
 int /*<<< orphan*/  cterefcount ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static void
_outCommonTableExpr(StringInfo str, const CommonTableExpr *node)
{
	WRITE_NODE_TYPE("COMMONTABLEEXPR");

	WRITE_STRING_FIELD(ctename);
	WRITE_NODE_FIELD(aliascolnames);
	WRITE_ENUM_FIELD(ctematerialized, CTEMaterialize);
	WRITE_NODE_FIELD(ctequery);
	WRITE_LOCATION_FIELD(location);
	WRITE_BOOL_FIELD(cterecursive);
	WRITE_INT_FIELD(cterefcount);
	WRITE_NODE_FIELD(ctecolnames);
	WRITE_NODE_FIELD(ctecoltypes);
	WRITE_NODE_FIELD(ctecoltypmods);
	WRITE_NODE_FIELD(ctecolcollations);
}