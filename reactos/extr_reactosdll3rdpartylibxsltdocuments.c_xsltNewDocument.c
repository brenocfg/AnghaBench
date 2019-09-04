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
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltDocumentPtr ;
typedef  int /*<<< orphan*/  xsltDocument ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  scalar_t__ xmlDocPtr ;
struct TYPE_8__ {struct TYPE_8__* next; scalar_t__ doc; } ;
struct TYPE_7__ {TYPE_2__* docList; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_IS_RES_TREE_FRAG (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

xsltDocumentPtr
xsltNewDocument(xsltTransformContextPtr ctxt, xmlDocPtr doc) {
    xsltDocumentPtr cur;

    cur = (xsltDocumentPtr) xmlMalloc(sizeof(xsltDocument));
    if (cur == NULL) {
	xsltTransformError(ctxt, NULL, (xmlNodePtr) doc,
		"xsltNewDocument : malloc failed\n");
	return(NULL);
    }
    memset(cur, 0, sizeof(xsltDocument));
    cur->doc = doc;
    if (ctxt != NULL) {
        if (! XSLT_IS_RES_TREE_FRAG(doc)) {
	    cur->next = ctxt->docList;
	    ctxt->docList = cur;
	}
	/*
	* A key with a specific name for a specific document
	* will only be computed if there's a call to the key()
	* function using that specific name for that specific
	* document. I.e. computation of keys will be done in
	* xsltGetKey() (keys.c) on an on-demand basis.
	*
	* xsltInitCtxtKeys(ctxt, cur); not called here anymore
	*/
    }
    return(cur);
}