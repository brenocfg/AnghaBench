#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltStylesheetPtr ;
typedef  TYPE_4__* xsltKeyDefPtr ;
typedef  TYPE_5__* xsltDocumentPtr ;
struct TYPE_18__ {TYPE_1__* doc; } ;
struct TYPE_17__ {struct TYPE_17__* next; } ;
struct TYPE_16__ {scalar_t__ keys; } ;
struct TYPE_15__ {TYPE_3__* style; } ;
struct TYPE_14__ {int /*<<< orphan*/ * URL; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_KEYS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltInitCtxtKey (TYPE_2__*,TYPE_5__*,TYPE_4__*) ; 
 TYPE_3__* xsltNextImport (TYPE_3__*) ; 

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