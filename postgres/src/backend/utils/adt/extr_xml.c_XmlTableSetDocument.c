#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmltype ;
typedef  TYPE_1__* xmlXPathContextPtr ;
typedef  scalar_t__ xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_8__ {TYPE_1__* xpathcxt; int /*<<< orphan*/ * doc; TYPE_3__* xmlerrcxt; int /*<<< orphan*/  ctxt; } ;
typedef  TYPE_2__ XmlTableBuilderData ;
typedef  int /*<<< orphan*/  TableFuncScanState ;
struct TYPE_9__ {scalar_t__ err_occurred; } ;
struct TYPE_7__ {scalar_t__ node; } ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetXmlP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_XML_DOCUMENT ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* GetXmlTableBuilderPrivateData (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NO_XML_SUPPORT () ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/ * pg_xmlCharStrndup (char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * xmlCtxtReadMemory (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ * volatile) ; 
 int /*<<< orphan*/  xmlXPathFreeContext (TYPE_1__* volatile) ; 
 TYPE_1__* xmlXPathNewContext (int /*<<< orphan*/ * volatile) ; 
 int /*<<< orphan*/  xml_ereport (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* xml_out_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
XmlTableSetDocument(TableFuncScanState *state, Datum value)
{
#ifdef USE_LIBXML
	XmlTableBuilderData *xtCxt;
	xmltype    *xmlval = DatumGetXmlP(value);
	char	   *str;
	xmlChar    *xstr;
	int			length;
	volatile xmlDocPtr doc = NULL;
	volatile xmlXPathContextPtr xpathcxt = NULL;

	xtCxt = GetXmlTableBuilderPrivateData(state, "XmlTableSetDocument");

	/*
	 * Use out function for casting to string (remove encoding property). See
	 * comment in xml_out.
	 */
	str = xml_out_internal(xmlval, 0);

	length = strlen(str);
	xstr = pg_xmlCharStrndup(str, length);

	PG_TRY();
	{
		doc = xmlCtxtReadMemory(xtCxt->ctxt, (char *) xstr, length, NULL, NULL, 0);
		if (doc == NULL || xtCxt->xmlerrcxt->err_occurred)
			xml_ereport(xtCxt->xmlerrcxt, ERROR, ERRCODE_INVALID_XML_DOCUMENT,
						"could not parse XML document");
		xpathcxt = xmlXPathNewContext(doc);
		if (xpathcxt == NULL || xtCxt->xmlerrcxt->err_occurred)
			xml_ereport(xtCxt->xmlerrcxt, ERROR, ERRCODE_OUT_OF_MEMORY,
						"could not allocate XPath context");
		xpathcxt->node = (xmlNodePtr) doc;
	}
	PG_CATCH();
	{
		if (xpathcxt != NULL)
			xmlXPathFreeContext(xpathcxt);
		if (doc != NULL)
			xmlFreeDoc(doc);

		PG_RE_THROW();
	}
	PG_END_TRY();

	xtCxt->doc = doc;
	xtCxt->xpathcxt = xpathcxt;
#else
	NO_XML_SUPPORT();
#endif							/* not USE_LIBXML */
}