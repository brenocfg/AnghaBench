#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/ * xsltDecimalFormatPtr ;
typedef  int /*<<< orphan*/  xmlXPathParserContextPtr ;
typedef  TYPE_3__* xmlXPathObjectPtr ;
typedef  TYPE_4__* xmlNsPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_16__ {int /*<<< orphan*/ * href; } ;
struct TYPE_15__ {int /*<<< orphan*/  floatval; int /*<<< orphan*/  stringval; } ;
struct TYPE_14__ {int /*<<< orphan*/  errors; int /*<<< orphan*/  dict; int /*<<< orphan*/ * decimalFormat; } ;
struct TYPE_13__ {TYPE_10__* inst; TYPE_2__* style; } ;
struct TYPE_12__ {int /*<<< orphan*/  doc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_TO_NUMBER ; 
 int /*<<< orphan*/  CAST_TO_STRING ; 
 scalar_t__ XPATH_EXPRESSION_OK ; 
 int /*<<< orphan*/  XPATH_INVALID_ARITY ; 
 int /*<<< orphan*/  XP_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_3__* valuePop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valuePush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 TYPE_4__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlXPathNewString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xsltDecimalFormatGetByQName (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ xsltFormatNumberConversion (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xsltSplitQName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* xsltXPathGetTransformContext (int /*<<< orphan*/ ) ; 

void
xsltFormatNumberFunction(xmlXPathParserContextPtr ctxt, int nargs)
{
    xmlXPathObjectPtr numberObj = NULL;
    xmlXPathObjectPtr formatObj = NULL;
    xmlXPathObjectPtr decimalObj = NULL;
    xsltStylesheetPtr sheet;
    xsltDecimalFormatPtr formatValues = NULL;
    xmlChar *result;
    const xmlChar *ncname;
    const xmlChar *prefix = NULL;
    const xmlChar *nsUri = NULL;
    xsltTransformContextPtr tctxt;

    tctxt = xsltXPathGetTransformContext(ctxt);
    if ((tctxt == NULL) || (tctxt->inst == NULL))
	return;
    sheet = tctxt->style;
    if (sheet == NULL)
	return;
    formatValues = sheet->decimalFormat;

    switch (nargs) {
    case 3:
	CAST_TO_STRING;
	decimalObj = valuePop(ctxt);
        ncname = xsltSplitQName(sheet->dict, decimalObj->stringval, &prefix);
        if (prefix != NULL) {
            xmlNsPtr ns = xmlSearchNs(tctxt->inst->doc, tctxt->inst, prefix);
            if (ns == NULL) {
                xsltTransformError(tctxt, NULL, NULL,
                    "format-number : No namespace found for QName '%s:%s'\n",
                    prefix, ncname);
                sheet->errors++;
                ncname = NULL;
            }
            else {
                nsUri = ns->href;
            }
        }
        if (ncname != NULL) {
	    formatValues = xsltDecimalFormatGetByQName(sheet, nsUri, ncname);
        }
	if (formatValues == NULL) {
	    xsltTransformError(tctxt, NULL, NULL,
		    "format-number() : undeclared decimal format '%s'\n",
		    decimalObj->stringval);
	}
	/* Intentional fall-through */
    case 2:
	CAST_TO_STRING;
	formatObj = valuePop(ctxt);
	CAST_TO_NUMBER;
	numberObj = valuePop(ctxt);
	break;
    default:
	XP_ERROR(XPATH_INVALID_ARITY);
    }

    if (formatValues != NULL) {
	if (xsltFormatNumberConversion(formatValues,
				       formatObj->stringval,
				       numberObj->floatval,
				       &result) == XPATH_EXPRESSION_OK) {
	    valuePush(ctxt, xmlXPathNewString(result));
	    xmlFree(result);
	}
    }

    xmlXPathFreeObject(numberObj);
    xmlXPathFreeObject(formatObj);
    xmlXPathFreeObject(decimalObj);
}