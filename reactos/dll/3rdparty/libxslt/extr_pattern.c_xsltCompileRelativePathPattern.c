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
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {int error; } ;

/* Variables and functions */
 char CUR ; 
 int /*<<< orphan*/  NEXT ; 
 char NXT (int) ; 
 int /*<<< orphan*/  PUSH (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  XSLT_OP_ANCESTOR ; 
 int /*<<< orphan*/  XSLT_OP_PARENT ; 
 int /*<<< orphan*/  xsltCompileStepPattern (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
xsltCompileRelativePathPattern(xsltParserContextPtr ctxt, xmlChar *token, int novar) {
    xsltCompileStepPattern(ctxt, token, novar);
    if (ctxt->error)
	goto error;
    SKIP_BLANKS;
    while ((CUR != 0) && (CUR != '|')) {
	if ((CUR == '/') && (NXT(1) == '/')) {
	    PUSH(XSLT_OP_ANCESTOR, NULL, NULL, novar);
	    NEXT;
	    NEXT;
	    SKIP_BLANKS;
	    xsltCompileStepPattern(ctxt, NULL, novar);
	} else if (CUR == '/') {
	    PUSH(XSLT_OP_PARENT, NULL, NULL, novar);
	    NEXT;
	    SKIP_BLANKS;
	    if ((CUR != 0) && (CUR != '|')) {
		xsltCompileRelativePathPattern(ctxt, NULL, novar);
	    }
	} else {
	    ctxt->error = 1;
	}
	if (ctxt->error)
	    goto error;
	SKIP_BLANKS;
    }
error:
    return;
}