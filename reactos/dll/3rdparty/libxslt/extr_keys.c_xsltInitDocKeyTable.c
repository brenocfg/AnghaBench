#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylesheetPtr ;
typedef  TYPE_3__* xsltKeyDefPtr ;
typedef  char xmlChar ;
struct TYPE_15__ {scalar_t__ nbKeysComputed; } ;
struct TYPE_14__ {int /*<<< orphan*/ * inst; struct TYPE_14__* next; int /*<<< orphan*/ * nameURI; int /*<<< orphan*/ * name; } ;
struct TYPE_13__ {scalar_t__ keys; } ;
struct TYPE_12__ {scalar_t__ nbKeys; int /*<<< orphan*/  state; TYPE_9__* document; TYPE_2__* style; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  XSLT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_KEYS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltInitCtxtKey (TYPE_1__*,TYPE_9__*,TYPE_3__*) ; 
 TYPE_2__* xsltNextImport (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int
xsltInitDocKeyTable(xsltTransformContextPtr ctxt, const xmlChar *name,
                    const xmlChar *nameURI)
{
    xsltStylesheetPtr style;
    xsltKeyDefPtr keyd = NULL;
    int found = 0;

#ifdef KEY_INIT_DEBUG
fprintf(stderr, "xsltInitDocKeyTable %s\n", name);
#endif

    style = ctxt->style;
    while (style != NULL) {
	keyd = (xsltKeyDefPtr) style->keys;
	while (keyd != NULL) {
	    if (((keyd->nameURI != NULL) ==
		 (nameURI != NULL)) &&
		xmlStrEqual(keyd->name, name) &&
		xmlStrEqual(keyd->nameURI, nameURI))
	    {
		xsltInitCtxtKey(ctxt, ctxt->document, keyd);
		if (ctxt->document->nbKeysComputed == ctxt->nbKeys)
		    return(0);
		found = 1;
	    }
	    keyd = keyd->next;
	}
	style = xsltNextImport(style);
    }
    if (found == 0) {
#ifdef WITH_XSLT_DEBUG_KEYS
	XSLT_TRACE(ctxt,XSLT_TRACE_KEYS,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltInitDocKeyTable: did not found %s\n", name));
#endif
	xsltTransformError(ctxt, NULL, keyd? keyd->inst : NULL,
	    "Failed to find key definition for %s\n", name);
	ctxt->state = XSLT_STATE_STOPPED;
        return(-1);
    }
#ifdef KEY_INIT_DEBUG
fprintf(stderr, "xsltInitDocKeyTable %s done\n", name);
#endif
    return(0);
}