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
typedef  int /*<<< orphan*/  xmlDocPtr ;
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  XmlOptionType ;

/* Variables and functions */
 int /*<<< orphan*/  GetDatabaseEncoding () ; 
 int /*<<< orphan*/  NO_XML_SUPPORT () ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

xmltype *
xmlparse(text *data, XmlOptionType xmloption_arg, bool preserve_whitespace)
{
#ifdef USE_LIBXML
	xmlDocPtr	doc;

	doc = xml_parse(data, xmloption_arg, preserve_whitespace,
					GetDatabaseEncoding());
	xmlFreeDoc(doc);

	return (xmltype *) data;
#else
	NO_XML_SUPPORT();
	return NULL;
#endif
}