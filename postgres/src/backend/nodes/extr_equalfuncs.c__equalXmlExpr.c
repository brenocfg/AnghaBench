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

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_names ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  named_args ; 
 int /*<<< orphan*/  op ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  typmod ; 
 int /*<<< orphan*/  xmloption ; 

__attribute__((used)) static bool
_equalXmlExpr(const XmlExpr *a, const XmlExpr *b)
{
	COMPARE_SCALAR_FIELD(op);
	COMPARE_STRING_FIELD(name);
	COMPARE_NODE_FIELD(named_args);
	COMPARE_NODE_FIELD(arg_names);
	COMPARE_NODE_FIELD(args);
	COMPARE_SCALAR_FIELD(xmloption);
	COMPARE_SCALAR_FIELD(type);
	COMPARE_SCALAR_FIELD(typmod);
	COMPARE_LOCATION_FIELD(location);

	return true;
}