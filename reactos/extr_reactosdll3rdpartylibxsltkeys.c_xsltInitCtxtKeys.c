#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylesheetPtr ;
typedef  TYPE_3__* xsltKeyDefPtr ;
typedef  int /*<<< orphan*/ * xsltDocumentPtr ;
struct TYPE_11__ {struct TYPE_11__* next; } ;
struct TYPE_10__ {scalar_t__ keys; } ;
struct TYPE_9__ {TYPE_2__* style; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsltInitCtxtKey (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_2__* xsltNextImport (TYPE_2__*) ; 

void
xsltInitCtxtKeys(xsltTransformContextPtr ctxt, xsltDocumentPtr idoc) {
    xsltStylesheetPtr style;
    xsltKeyDefPtr keyDef;

    if ((ctxt == NULL) || (idoc == NULL))
	return;

#ifdef KEY_INIT_DEBUG
fprintf(stderr, "xsltInitCtxtKeys on document\n");
#endif

#ifdef WITH_XSLT_DEBUG_KEYS
    if ((idoc->doc != NULL) && (idoc->doc->URL != NULL))
	XSLT_TRACE(ctxt,XSLT_TRACE_KEYS,xsltGenericDebug(xsltGenericDebugContext, "Initializing keys on %s\n",
		     idoc->doc->URL));
#endif
    style = ctxt->style;
    while (style != NULL) {
	keyDef = (xsltKeyDefPtr) style->keys;
	while (keyDef != NULL) {
	    xsltInitCtxtKey(ctxt, idoc, keyDef);

	    keyDef = keyDef->next;
	}

	style = xsltNextImport(style);
    }

#ifdef KEY_INIT_DEBUG
fprintf(stderr, "xsltInitCtxtKeys on document: done\n");
#endif

}