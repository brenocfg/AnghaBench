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
typedef  TYPE_1__* xsltParserContextPtr ;
typedef  scalar_t__ xsltAxis ;
typedef  TYPE_2__* xmlNsPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_8__ {int /*<<< orphan*/  const* href; } ;
struct TYPE_7__ {int error; int /*<<< orphan*/  elem; int /*<<< orphan*/  doc; } ;

/* Variables and functions */
 scalar_t__ AXIS_ATTRIBUTE ; 
 scalar_t__ AXIS_CHILD ; 
 char CUR ; 
 int /*<<< orphan*/  const* CUR_PTR ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  PUSH (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  SWAP () ; 
 int /*<<< orphan*/  XSLT_OP_ALL ; 
 int /*<<< orphan*/  XSLT_OP_ATTR ; 
 int /*<<< orphan*/  XSLT_OP_ELEM ; 
 int /*<<< orphan*/  XSLT_OP_NS ; 
 int /*<<< orphan*/  XSLT_OP_PREDICATE ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 TYPE_2__* xmlSearchNs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xmlStrndup (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  xsltCompileIdKeyPattern (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/ * xsltGetQNameURI (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xsltScanNCName (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
xsltCompileStepPattern(xsltParserContextPtr ctxt, xmlChar *token, int novar) {
    xmlChar *name = NULL;
    const xmlChar *URI = NULL;
    xmlChar *URL = NULL;
    int level;
    xsltAxis axis = 0;

    SKIP_BLANKS;
    if ((token == NULL) && (CUR == '@')) {
	NEXT;
        axis = AXIS_ATTRIBUTE;
    }
parse_node_test:
    if (token == NULL)
	token = xsltScanNCName(ctxt);
    if (token == NULL) {
	if (CUR == '*') {
	    NEXT;
	    if (axis == AXIS_ATTRIBUTE) {
                PUSH(XSLT_OP_ATTR, NULL, NULL, novar);
            }
            else {
                PUSH(XSLT_OP_ALL, NULL, NULL, novar);
            }
	    goto parse_predicate;
	} else {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileStepPattern : Name expected\n");
	    ctxt->error = 1;
	    goto error;
	}
    }


    SKIP_BLANKS;
    if (CUR == '(') {
	xsltCompileIdKeyPattern(ctxt, token, 0, novar, axis);
	xmlFree(token);
	token = NULL;
	if (ctxt->error)
	    goto error;
    } else if (CUR == ':') {
	NEXT;
	if (CUR != ':') {
	    xmlChar *prefix = token;
	    xmlNsPtr ns;

	    /*
	     * This is a namespace match
	     */
	    token = xsltScanNCName(ctxt);
	    ns = xmlSearchNs(ctxt->doc, ctxt->elem, prefix);
	    if (ns == NULL) {
		xsltTransformError(NULL, NULL, NULL,
	    "xsltCompileStepPattern : no namespace bound to prefix %s\n",
				 prefix);
		xmlFree(prefix);
		prefix=NULL;
		ctxt->error = 1;
		goto error;
	    } else {
		URL = xmlStrdup(ns->href);
	    }
	    xmlFree(prefix);
	    prefix=NULL;
	    if (token == NULL) {
		if (CUR == '*') {
		    NEXT;
                    if (axis == AXIS_ATTRIBUTE) {
                        PUSH(XSLT_OP_ATTR, NULL, URL, novar);
			URL = NULL;
                    }
                    else {
                        PUSH(XSLT_OP_NS, URL, NULL, novar);
			URL = NULL;
                    }
		} else {
		    xsltTransformError(NULL, NULL, NULL,
			    "xsltCompileStepPattern : Name expected\n");
		    ctxt->error = 1;
                    xmlFree(URL);
		    goto error;
		}
	    } else {
                if (axis == AXIS_ATTRIBUTE) {
                    PUSH(XSLT_OP_ATTR, token, URL, novar);
		    token = NULL;
		    URL = NULL;
                }
                else {
                    PUSH(XSLT_OP_ELEM, token, URL, novar);
		    token = NULL;
		    URL = NULL;
                }
	    }
	} else {
	    if (axis != 0) {
		xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileStepPattern : NodeTest expected\n");
		ctxt->error = 1;
		goto error;
	    }
	    NEXT;
	    if (xmlStrEqual(token, (const xmlChar *) "child")) {
	        axis = AXIS_CHILD;
	    } else if (xmlStrEqual(token, (const xmlChar *) "attribute")) {
	        axis = AXIS_ATTRIBUTE;
	    } else {
		xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileStepPattern : 'child' or 'attribute' expected\n");
		ctxt->error = 1;
		goto error;
	    }
	    xmlFree(token);
	    token = NULL;
            SKIP_BLANKS;
            token = xsltScanNCName(ctxt);
	    goto parse_node_test;
	}
    } else {
	URI = xsltGetQNameURI(ctxt->elem, &token);
	if (token == NULL) {
	    ctxt->error = 1;
	    goto error;
	}
	if (URI != NULL)
	    URL = xmlStrdup(URI);
        if (axis == AXIS_ATTRIBUTE) {
            PUSH(XSLT_OP_ATTR, token, URL, novar);
	    token = NULL;
	    URL = NULL;
        }
        else {
            PUSH(XSLT_OP_ELEM, token, URL, novar);
	    token = NULL;
	    URL = NULL;
        }
    }
parse_predicate:
    SKIP_BLANKS;
    level = 0;
    while (CUR == '[') {
	const xmlChar *q;
	xmlChar *ret = NULL;

	level++;
	NEXT;
	q = CUR_PTR;
	while (CUR != 0) {
	    /* Skip over nested predicates */
	    if (CUR == '[')
		level++;
	    else if (CUR == ']') {
		level--;
		if (level == 0)
		    break;
	    } else if (CUR == '"') {
		NEXT;
		while ((CUR != 0) && (CUR != '"'))
		    NEXT;
	    } else if (CUR == '\'') {
		NEXT;
		while ((CUR != 0) && (CUR != '\''))
		    NEXT;
	    }
	    NEXT;
	}
	if (CUR == 0) {
	    xsltTransformError(NULL, NULL, NULL,
		    "xsltCompileStepPattern : ']' expected\n");
	    ctxt->error = 1;
	    return;
        }
	ret = xmlStrndup(q, CUR_PTR - q);
	PUSH(XSLT_OP_PREDICATE, ret, NULL, novar);
	ret = NULL;
	/* push the predicate lower than local test */
	SWAP();
	NEXT;
	SKIP_BLANKS;
    }
    return;
error:
    if (token != NULL)
	xmlFree(token);
    if (name != NULL)
	xmlFree(name);
}