#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/  text ;
struct TYPE_3__ {int type; int /*<<< orphan*/  const* stringval; int /*<<< orphan*/  nodesetval; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTICE ; 
#define  XPATH_NODESET 129 
#define  XPATH_STRING 128 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * pgxmlNodeSetToText (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static text *
pgxml_result_to_text(xmlXPathObjectPtr res,
					 xmlChar *toptag,
					 xmlChar *septag,
					 xmlChar *plainsep)
{
	xmlChar    *xpresstr;
	text	   *xpres;

	if (res == NULL)
		return NULL;

	switch (res->type)
	{
		case XPATH_NODESET:
			xpresstr = pgxmlNodeSetToText(res->nodesetval,
										  toptag,
										  septag, plainsep);
			break;

		case XPATH_STRING:
			xpresstr = xmlStrdup(res->stringval);
			break;

		default:
			elog(NOTICE, "unsupported XQuery result: %d", res->type);
			xpresstr = xmlStrdup((const xmlChar *) "<unsupported/>");
	}

	/* Now convert this result back to text */
	xpres = cstring_to_text((char *) xpresstr);

	/* Free various storage */
	xmlFree(xpresstr);

	return xpres;
}