#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltParserContextPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_8__ {int error; TYPE_1__* comp; } ;
struct TYPE_7__ {double priority; } ;

/* Variables and functions */
 char CUR ; 
 int /*<<< orphan*/  NEXT ; 
 char NXT (int) ; 
 int /*<<< orphan*/  PUSH (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  XSLT_OP_ANCESTOR ; 
 int /*<<< orphan*/  XSLT_OP_PARENT ; 
 int /*<<< orphan*/  XSLT_OP_ROOT ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlXPathIsNodeType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltCompileIdKeyPattern (TYPE_2__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltCompileRelativePathPattern (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xsltScanNCName (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
xsltCompileLocationPathPattern(xsltParserContextPtr ctxt, int novar) {
    SKIP_BLANKS;
    if ((CUR == '/') && (NXT(1) == '/')) {
	/*
	 * since we reverse the query
	 * a leading // can be safely ignored
	 */
	NEXT;
	NEXT;
	ctxt->comp->priority = 0.5;	/* '//' means not 0 priority */
	xsltCompileRelativePathPattern(ctxt, NULL, novar);
    } else if (CUR == '/') {
	/*
	 * We need to find root as the parent
	 */
	NEXT;
	SKIP_BLANKS;
	PUSH(XSLT_OP_ROOT, NULL, NULL, novar);
	if ((CUR != 0) && (CUR != '|')) {
	    PUSH(XSLT_OP_PARENT, NULL, NULL, novar);
	    xsltCompileRelativePathPattern(ctxt, NULL, novar);
	}
    } else if (CUR == '*') {
	xsltCompileRelativePathPattern(ctxt, NULL, novar);
    } else if (CUR == '@') {
	xsltCompileRelativePathPattern(ctxt, NULL, novar);
    } else {
	xmlChar *name;
	name = xsltScanNCName(ctxt);
	if (name == NULL) {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileLocationPathPattern : Name expected\n");
	    ctxt->error = 1;
	    return;
	}
	SKIP_BLANKS;
	if ((CUR == '(') && !xmlXPathIsNodeType(name)) {
	    xsltCompileIdKeyPattern(ctxt, name, 1, novar, 0);
	    xmlFree(name);
	    name = NULL;
	    if ((CUR == '/') && (NXT(1) == '/')) {
		PUSH(XSLT_OP_ANCESTOR, NULL, NULL, novar);
		NEXT;
		NEXT;
		SKIP_BLANKS;
		xsltCompileRelativePathPattern(ctxt, NULL, novar);
	    } else if (CUR == '/') {
		PUSH(XSLT_OP_PARENT, NULL, NULL, novar);
		NEXT;
		SKIP_BLANKS;
		xsltCompileRelativePathPattern(ctxt, NULL, novar);
	    }
	    return;
	}
	xsltCompileRelativePathPattern(ctxt, name, novar);
    }
error:
    return;
}