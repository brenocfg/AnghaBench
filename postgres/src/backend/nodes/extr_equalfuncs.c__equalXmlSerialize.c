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
typedef  int /*<<< orphan*/  XmlSerialize ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  typeName ; 
 int /*<<< orphan*/  xmloption ; 

__attribute__((used)) static bool
_equalXmlSerialize(const XmlSerialize *a, const XmlSerialize *b)
{
	COMPARE_SCALAR_FIELD(xmloption);
	COMPARE_NODE_FIELD(expr);
	COMPARE_NODE_FIELD(typeName);
	COMPARE_LOCATION_FIELD(location);

	return true;
}