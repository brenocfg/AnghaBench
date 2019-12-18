#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltParserContextPtr ;
typedef  scalar_t__ xsltAxis ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {int error; } ;

/* Variables and functions */
 scalar_t__ AXIS_ATTRIBUTE ; 
 char CUR ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  PUSH (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  XSLT_OP_ATTR ; 
 int /*<<< orphan*/  XSLT_OP_COMMENT ; 
 int /*<<< orphan*/  XSLT_OP_ID ; 
 int /*<<< orphan*/  XSLT_OP_KEY ; 
 int /*<<< orphan*/  XSLT_OP_NODE ; 
 int /*<<< orphan*/  XSLT_OP_PI ; 
 int /*<<< orphan*/  XSLT_OP_TEXT ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xsltScanLiteral (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
xsltCompileIdKeyPattern(xsltParserContextPtr ctxt, xmlChar *name,
		int aid, int novar, xsltAxis axis) {
    xmlChar *lit = NULL;
    xmlChar *lit2 = NULL;

    if (CUR != '(') {
	xsltTransformError(NULL, NULL, NULL,
		"xsltCompileIdKeyPattern : ( expected\n");
	ctxt->error = 1;
	return;
    }
    if ((aid) && (xmlStrEqual(name, (const xmlChar *)"id"))) {
	if (axis != 0) {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : NodeTest expected\n");
	    ctxt->error = 1;
	    return;
	}
	NEXT;
	SKIP_BLANKS;
        lit = xsltScanLiteral(ctxt);
	if (ctxt->error) {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : Literal expected\n");
	    return;
	}
	SKIP_BLANKS;
	if (CUR != ')') {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : ) expected\n");
	    xmlFree(lit);
	    ctxt->error = 1;
	    return;
	}
	NEXT;
	PUSH(XSLT_OP_ID, lit, NULL, novar);
	lit = NULL;
    } else if ((aid) && (xmlStrEqual(name, (const xmlChar *)"key"))) {
	if (axis != 0) {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : NodeTest expected\n");
	    ctxt->error = 1;
	    return;
	}
	NEXT;
	SKIP_BLANKS;
        lit = xsltScanLiteral(ctxt);
	if (ctxt->error) {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : Literal expected\n");
	    return;
	}
	SKIP_BLANKS;
	if (CUR != ',') {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : , expected\n");
	    xmlFree(lit);
	    ctxt->error = 1;
	    return;
	}
	NEXT;
	SKIP_BLANKS;
        lit2 = xsltScanLiteral(ctxt);
	if (ctxt->error) {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : Literal expected\n");
	    xmlFree(lit);
	    return;
	}
	SKIP_BLANKS;
	if (CUR != ')') {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : ) expected\n");
	    xmlFree(lit);
	    xmlFree(lit2);
	    ctxt->error = 1;
	    return;
	}
	NEXT;
	/* URGENT TODO: support namespace in keys */
	PUSH(XSLT_OP_KEY, lit, lit2, novar);
	lit = NULL;
	lit2 = NULL;
    } else if (xmlStrEqual(name, (const xmlChar *)"processing-instruction")) {
	NEXT;
	SKIP_BLANKS;
	if (CUR != ')') {
	    lit = xsltScanLiteral(ctxt);
	    if (ctxt->error) {
		xsltTransformError(NULL, NULL, NULL,
			"xsltCompileIdKeyPattern : Literal expected\n");
		return;
	    }
	    SKIP_BLANKS;
	    if (CUR != ')') {
		xsltTransformError(NULL, NULL, NULL,
			"xsltCompileIdKeyPattern : ) expected\n");
		ctxt->error = 1;
                xmlFree(lit);
		return;
	    }
	}
	NEXT;
	PUSH(XSLT_OP_PI, lit, NULL, novar);
	lit = NULL;
    } else if (xmlStrEqual(name, (const xmlChar *)"text")) {
	NEXT;
	SKIP_BLANKS;
	if (CUR != ')') {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : ) expected\n");
	    ctxt->error = 1;
	    return;
	}
	NEXT;
	PUSH(XSLT_OP_TEXT, NULL, NULL, novar);
    } else if (xmlStrEqual(name, (const xmlChar *)"comment")) {
	NEXT;
	SKIP_BLANKS;
	if (CUR != ')') {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : ) expected\n");
	    ctxt->error = 1;
	    return;
	}
	NEXT;
	PUSH(XSLT_OP_COMMENT, NULL, NULL, novar);
    } else if (xmlStrEqual(name, (const xmlChar *)"node")) {
	NEXT;
	SKIP_BLANKS;
	if (CUR != ')') {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileIdKeyPattern : ) expected\n");
	    ctxt->error = 1;
	    return;
	}
	NEXT;
	if (axis == AXIS_ATTRIBUTE) {
	    PUSH(XSLT_OP_ATTR, NULL, NULL, novar);
	}
	else {
	    PUSH(XSLT_OP_NODE, NULL, NULL, novar);
	}
    } else if (aid) {
	xsltTransformError(NULL, NULL, NULL,
	    "xsltCompileIdKeyPattern : expecting 'key' or 'id' or node type\n");
	ctxt->error = 1;
	return;
    } else {
	xsltTransformError(NULL, NULL, NULL,
	    "xsltCompileIdKeyPattern : node type\n");
	ctxt->error = 1;
	return;
    }
error:
    return;
}