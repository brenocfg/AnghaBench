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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  encodeTypePtr ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int SOAP_ENCODED ; 
 int /*<<< orphan*/  set_xsi_nil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlAddChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNewNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xmlNodePtr to_xml_null(encodeTypePtr type, zval *data, int style, xmlNodePtr parent)
{
	xmlNodePtr ret;

	ret = xmlNewNode(NULL, BAD_CAST("BOGUS"));
	xmlAddChild(parent, ret);
	if (style == SOAP_ENCODED) {
		set_xsi_nil(ret);
	}
	return ret;
}