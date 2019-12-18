#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltNumberDataPtr ;
struct TYPE_17__ {int nTokens; TYPE_1__* tokens; int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; } ;
typedef  TYPE_4__ xsltFormat ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/ * xmlBufferPtr ;
typedef  int /*<<< orphan*/  numarray ;
struct TYPE_16__ {scalar_t__ has_format; int /*<<< orphan*/  fromPat; int /*<<< orphan*/  countPat; scalar_t__ level; scalar_t__ value; int /*<<< orphan*/  node; int /*<<< orphan*/ * format; } ;
struct TYPE_15__ {int /*<<< orphan*/  insert; int /*<<< orphan*/  xpathCtxt; } ;
struct TYPE_14__ {int /*<<< orphan*/ * separator; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_NAMESPACE ; 
 int /*<<< orphan*/  xmlBufferContent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlStrEqual (scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltCopyTextString (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xsltEvalAttrValueTemplate (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int xsltNumberFormatGetAnyLevel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*) ; 
 int xsltNumberFormatGetMultipleLevel (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,int) ; 
 int xsltNumberFormatGetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,double*) ; 
 int /*<<< orphan*/  xsltNumberFormatInsertNumbers (TYPE_3__*,double*,int,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltNumberFormatTokenize (int /*<<< orphan*/ *,TYPE_4__*) ; 

void
xsltNumberFormat(xsltTransformContextPtr ctxt,
		 xsltNumberDataPtr data,
		 xmlNodePtr node)
{
    xmlBufferPtr output = NULL;
    int amount, i;
    double number;
    xsltFormat tokens;

    if (data->format != NULL) {
        xsltNumberFormatTokenize(data->format, &tokens);
    }
    else {
        xmlChar *format;

	/* The format needs to be recomputed each time */
        if (data->has_format == 0)
            return;
	format = xsltEvalAttrValueTemplate(ctxt, data->node,
					     (const xmlChar *) "format",
					     XSLT_NAMESPACE);
        if (format == NULL)
            return;
        xsltNumberFormatTokenize(format, &tokens);
	xmlFree(format);
    }

    output = xmlBufferCreate();
    if (output == NULL)
	goto XSLT_NUMBER_FORMAT_END;

    /*
     * Evaluate the XPath expression to find the value(s)
     */
    if (data->value) {
	amount = xsltNumberFormatGetValue(ctxt->xpathCtxt,
					  node,
					  data->value,
					  &number);
	if (amount == 1) {
	    xsltNumberFormatInsertNumbers(data,
					  &number,
					  1,
					  &tokens,
					  output);
	}

    } else if (data->level) {

	if (xmlStrEqual(data->level, (const xmlChar *) "single")) {
	    amount = xsltNumberFormatGetMultipleLevel(ctxt,
						      node,
						      data->countPat,
						      data->fromPat,
						      &number,
						      1);
	    if (amount == 1) {
		xsltNumberFormatInsertNumbers(data,
					      &number,
					      1,
					      &tokens,
					      output);
	    }
	} else if (xmlStrEqual(data->level, (const xmlChar *) "multiple")) {
	    double numarray[1024];
	    int max = sizeof(numarray)/sizeof(numarray[0]);
	    amount = xsltNumberFormatGetMultipleLevel(ctxt,
						      node,
						      data->countPat,
						      data->fromPat,
						      numarray,
						      max);
	    if (amount > 0) {
		xsltNumberFormatInsertNumbers(data,
					      numarray,
					      amount,
					      &tokens,
					      output);
	    }
	} else if (xmlStrEqual(data->level, (const xmlChar *) "any")) {
	    amount = xsltNumberFormatGetAnyLevel(ctxt,
						 node,
						 data->countPat,
						 data->fromPat,
						 &number);
	    if (amount > 0) {
		xsltNumberFormatInsertNumbers(data,
					      &number,
					      1,
					      &tokens,
					      output);
	    }
	}
    }
    /* Insert number as text node */
    xsltCopyTextString(ctxt, ctxt->insert, xmlBufferContent(output), 0);

    xmlBufferFree(output);

XSLT_NUMBER_FORMAT_END:
    if (tokens.start != NULL)
	xmlFree(tokens.start);
    if (tokens.end != NULL)
	xmlFree(tokens.end);
    for (i = 0;i < tokens.nTokens;i++) {
	if (tokens.tokens[i].separator != NULL)
	    xmlFree(tokens.tokens[i].separator);
    }
}