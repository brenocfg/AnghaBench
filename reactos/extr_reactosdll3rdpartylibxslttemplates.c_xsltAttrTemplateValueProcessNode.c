#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  int /*<<< orphan*/  xmlXPathCompExprPtr ;
typedef  int /*<<< orphan*/ * xmlNsPtr ;
typedef  TYPE_1__* xmlNodePtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_5__ {int /*<<< orphan*/  doc; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 int /*<<< orphan*/ ** xmlGetNsList (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__* xmlStrcat (scalar_t__*,scalar_t__*) ; 
 scalar_t__* xmlStrncat (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__* xmlStrndup (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  xmlXPathCompile (scalar_t__*) ; 
 int /*<<< orphan*/  xmlXPathFreeCompExpr (int /*<<< orphan*/ ) ; 
 scalar_t__* xsltEvalXPathStringNs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,char*) ; 

xmlChar *
xsltAttrTemplateValueProcessNode(xsltTransformContextPtr ctxt,
	  const xmlChar *str, xmlNodePtr inst)
{
    xmlChar *ret = NULL;
    const xmlChar *cur;
    xmlChar *expr, *val;
    xmlNsPtr *nsList = NULL;
    int nsNr = 0;

    if (str == NULL) return(NULL);
    if (*str == 0)
	return(xmlStrndup((xmlChar *)"", 0));

    cur = str;
    while (*cur != 0) {
	if (*cur == '{') {
	    if (*(cur+1) == '{') {	/* escaped '{' */
	        cur++;
		ret = xmlStrncat(ret, str, cur - str);
		cur++;
		str = cur;
		continue;
	    }
	    ret = xmlStrncat(ret, str, cur - str);
	    str = cur;
	    cur++;
	    while ((*cur != 0) && (*cur != '}')) {
		/* Need to check for literal (bug539741) */
		if ((*cur == '\'') || (*cur == '"')) {
		    char delim = *(cur++);
		    while ((*cur != 0) && (*cur != delim))
			cur++;
		    if (*cur != 0)
			cur++;	/* skip the ending delimiter */
		} else
		    cur++;
            }
	    if (*cur == 0) {
	        xsltTransformError(ctxt, NULL, inst,
			"xsltAttrTemplateValueProcessNode: unmatched '{'\n");
		ret = xmlStrncat(ret, str, cur - str);
		goto exit;
	    }
	    str++;
	    expr = xmlStrndup(str, cur - str);
	    if (expr == NULL)
		goto exit;
	    else if (*expr == '{') {
		ret = xmlStrcat(ret, expr);
		xmlFree(expr);
	    } else {
		xmlXPathCompExprPtr comp;
		/*
		 * TODO: keep precompiled form around
		 */
		if ((nsList == NULL) && (inst != NULL)) {
		    int i = 0;

		    nsList = xmlGetNsList(inst->doc, inst);
		    if (nsList != NULL) {
			while (nsList[i] != NULL)
			    i++;
			nsNr = i;
		    }
		}
		comp = xmlXPathCompile(expr);
                val = xsltEvalXPathStringNs(ctxt, comp, nsNr, nsList);
		xmlXPathFreeCompExpr(comp);
		xmlFree(expr);
		if (val != NULL) {
		    ret = xmlStrcat(ret, val);
		    xmlFree(val);
		}
	    }
	    cur++;
	    str = cur;
	} else if (*cur == '}') {
	    cur++;
	    if (*cur == '}') {	/* escaped '}' */
		ret = xmlStrncat(ret, str, cur - str);
		cur++;
		str = cur;
		continue;
	    } else {
	        xsltTransformError(ctxt, NULL, inst,
		     "xsltAttrTemplateValueProcessNode: unmatched '}'\n");
	    }
	} else
	    cur++;
    }
    if (cur != str) {
	ret = xmlStrncat(ret, str, cur - str);
    }

exit:
    if (nsList != NULL)
	xmlFree(nsList);

    return(ret);
}