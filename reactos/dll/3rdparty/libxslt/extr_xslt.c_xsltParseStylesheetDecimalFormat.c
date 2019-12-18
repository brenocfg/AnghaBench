#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltDecimalFormatPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_16__ {scalar_t__ type; int /*<<< orphan*/ * children; } ;
struct TYPE_15__ {int /*<<< orphan*/ * patternSeparator; int /*<<< orphan*/ * digit; int /*<<< orphan*/ * zeroDigit; int /*<<< orphan*/ * permille; int /*<<< orphan*/ * percent; int /*<<< orphan*/ * noNumber; int /*<<< orphan*/ * minusSign; int /*<<< orphan*/ * infinity; int /*<<< orphan*/ * grouping; int /*<<< orphan*/ * decimalPoint; struct TYPE_15__* next; } ;
struct TYPE_14__ {TYPE_2__* decimalFormat; int /*<<< orphan*/  errors; int /*<<< orphan*/  warnings; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* BAD_CAST (char*) ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlGetNsProp (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlValidateQName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* xsltDecimalFormatGetByQName (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xsltGetQNameURI (TYPE_3__*,int /*<<< orphan*/ **) ; 
 TYPE_2__* xsltNewDecimalFormat (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltParseContentError (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,char*,...) ; 

__attribute__((used)) static void
xsltParseStylesheetDecimalFormat(xsltStylesheetPtr style, xmlNodePtr cur)
{
    xmlChar *prop;
    xsltDecimalFormatPtr format;
    xsltDecimalFormatPtr iter;

    if ((cur == NULL) || (style == NULL) || (cur->type != XML_ELEMENT_NODE))
	return;

    format = style->decimalFormat;

    prop = xmlGetNsProp(cur, BAD_CAST("name"), NULL);
    if (prop != NULL) {
        const xmlChar *nsUri;

        if (xmlValidateQName(prop, 0) != 0) {
            xsltTransformError(NULL, style, cur,
                "xsl:decimal-format: Invalid QName '%s'.\n", prop);
	    style->warnings++;
            xmlFree(prop);
            return;
        }
        /*
        * TODO: Don't use xsltGetQNameURI().
        */
        nsUri = xsltGetQNameURI(cur, &prop);
        if (prop == NULL) {
	    style->warnings++;
            return;
        }
	format = xsltDecimalFormatGetByQName(style, nsUri, prop);
	if (format != NULL) {
	    xsltTransformError(NULL, style, cur,
	 "xsltParseStylestyleDecimalFormat: %s already exists\n", prop);
	    style->warnings++;
            xmlFree(prop);
	    return;
	}
	format = xsltNewDecimalFormat(nsUri, prop);
	if (format == NULL) {
	    xsltTransformError(NULL, style, cur,
     "xsltParseStylestyleDecimalFormat: failed creating new decimal-format\n");
	    style->errors++;
            xmlFree(prop);
	    return;
	}
	/* Append new decimal-format structure */
	for (iter = style->decimalFormat; iter->next; iter = iter->next)
	    ;
	if (iter)
	    iter->next = format;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"decimal-separator", NULL);
    if (prop != NULL) {
	if (format->decimalPoint != NULL) xmlFree(format->decimalPoint);
	format->decimalPoint  = prop;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"grouping-separator", NULL);
    if (prop != NULL) {
	if (format->grouping != NULL) xmlFree(format->grouping);
	format->grouping  = prop;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"infinity", NULL);
    if (prop != NULL) {
	if (format->infinity != NULL) xmlFree(format->infinity);
	format->infinity  = prop;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"minus-sign", NULL);
    if (prop != NULL) {
	if (format->minusSign != NULL) xmlFree(format->minusSign);
	format->minusSign  = prop;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"NaN", NULL);
    if (prop != NULL) {
	if (format->noNumber != NULL) xmlFree(format->noNumber);
	format->noNumber  = prop;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"percent", NULL);
    if (prop != NULL) {
	if (format->percent != NULL) xmlFree(format->percent);
	format->percent  = prop;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"per-mille", NULL);
    if (prop != NULL) {
	if (format->permille != NULL) xmlFree(format->permille);
	format->permille  = prop;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"zero-digit", NULL);
    if (prop != NULL) {
	if (format->zeroDigit != NULL) xmlFree(format->zeroDigit);
	format->zeroDigit  = prop;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"digit", NULL);
    if (prop != NULL) {
	if (format->digit != NULL) xmlFree(format->digit);
	format->digit  = prop;
    }

    prop = xmlGetNsProp(cur, (const xmlChar *)"pattern-separator", NULL);
    if (prop != NULL) {
	if (format->patternSeparator != NULL) xmlFree(format->patternSeparator);
	format->patternSeparator  = prop;
    }
    if (cur->children != NULL) {
	xsltParseContentError(style, cur->children);
    }
}