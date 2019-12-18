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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  XmlOptionType ; 
 int /*<<< orphan*/  expr ; 
 int /*<<< orphan*/  location ; 
 int /*<<< orphan*/  typeName ; 
 int /*<<< orphan*/  xmloption ; 

__attribute__((used)) static void
_outXmlSerialize(StringInfo str, const XmlSerialize *node)
{
	WRITE_NODE_TYPE("XMLSERIALIZE");

	WRITE_ENUM_FIELD(xmloption, XmlOptionType);
	WRITE_NODE_FIELD(expr);
	WRITE_NODE_FIELD(typeName);
	WRITE_LOCATION_FIELD(location);
}