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
typedef  int /*<<< orphan*/  XmlExpr ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmlExprOp ; 
 int /*<<< orphan*/  XmlOptionType ; 
 int /*<<< orphan*/  arg_names ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  named_args ; 
 int /*<<< orphan*/  op ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  typmod ; 
 int /*<<< orphan*/  xmloption ; 

__attribute__((used)) static void
_outXmlExpr(StringInfo str, const XmlExpr *node)
{
	WRITE_NODE_TYPE("XMLEXPR");

	WRITE_ENUM_FIELD(op, XmlExprOp);
	WRITE_STRING_FIELD(name);
	WRITE_NODE_FIELD(named_args);
	WRITE_NODE_FIELD(arg_names);
	WRITE_NODE_FIELD(args);
	WRITE_ENUM_FIELD(xmloption, XmlOptionType);
	WRITE_OID_FIELD(type);
	WRITE_INT_FIELD(typmod);
	WRITE_LOCATION_FIELD(location);
}