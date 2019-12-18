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
typedef  int /*<<< orphan*/  xmltype ;
typedef  int /*<<< orphan*/  text ;
typedef  scalar_t__ XmlOptionType ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_NOT_AN_XML_DOCUMENT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ XMLOPTION_DOCUMENT ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  xml_is_document (int /*<<< orphan*/ *) ; 

text *
xmltotext_with_xmloption(xmltype *data, XmlOptionType xmloption_arg)
{
	if (xmloption_arg == XMLOPTION_DOCUMENT && !xml_is_document(data))
		ereport(ERROR,
				(errcode(ERRCODE_NOT_AN_XML_DOCUMENT),
				 errmsg("not an XML document")));

	/* It's actually binary compatible, save for the above check. */
	return (text *) data;
}