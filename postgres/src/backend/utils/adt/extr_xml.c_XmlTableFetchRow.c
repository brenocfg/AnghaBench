#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* xpathobj; scalar_t__ row_count; TYPE_3__* xmlerrcxt; int /*<<< orphan*/  xpathcxt; int /*<<< orphan*/  xpathcomp; } ;
typedef  TYPE_2__ XmlTableBuilderData ;
typedef  int /*<<< orphan*/  TableFuncScanState ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__* nodesetval; } ;
struct TYPE_8__ {scalar_t__ err_occurred; } ;
struct TYPE_6__ {scalar_t__ nodeNr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* GetXmlTableBuilderPrivateData (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NO_XML_SUPPORT () ; 
 scalar_t__ XPATH_NODESET ; 
 int /*<<< orphan*/  xmlSetStructuredErrorFunc (void*,int /*<<< orphan*/ ) ; 
 TYPE_4__* xmlXPathCompiledEval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_ereport (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xml_errorHandler ; 

__attribute__((used)) static bool
XmlTableFetchRow(TableFuncScanState *state)
{
#ifdef USE_LIBXML
	XmlTableBuilderData *xtCxt;

	xtCxt = GetXmlTableBuilderPrivateData(state, "XmlTableFetchRow");

	/*
	 * XmlTable returns table - set of composite values. The error context, is
	 * used for producement more values, between two calls, there can be
	 * created and used another libxml2 error context. It is libxml2 global
	 * value, so it should be refreshed any time before any libxml2 usage,
	 * that is finished by returning some value.
	 */
	xmlSetStructuredErrorFunc((void *) xtCxt->xmlerrcxt, xml_errorHandler);

	if (xtCxt->xpathobj == NULL)
	{
		xtCxt->xpathobj = xmlXPathCompiledEval(xtCxt->xpathcomp, xtCxt->xpathcxt);
		if (xtCxt->xpathobj == NULL || xtCxt->xmlerrcxt->err_occurred)
			xml_ereport(xtCxt->xmlerrcxt, ERROR, ERRCODE_INTERNAL_ERROR,
						"could not create XPath object");

		xtCxt->row_count = 0;
	}

	if (xtCxt->xpathobj->type == XPATH_NODESET)
	{
		if (xtCxt->xpathobj->nodesetval != NULL)
		{
			if (xtCxt->row_count++ < xtCxt->xpathobj->nodesetval->nodeNr)
				return true;
		}
	}

	return false;
#else
	NO_XML_SUPPORT();
	return false;
#endif							/* not USE_LIBXML */
}