#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltKeyTablePtr ;
typedef  int /*<<< orphan*/ * xmlNodeSetPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/  keys; int /*<<< orphan*/ * nameURI; int /*<<< orphan*/ * name; } ;
struct TYPE_8__ {scalar_t__ nbKeys; scalar_t__ keyInitLevel; TYPE_1__* document; } ;
struct TYPE_7__ {scalar_t__ nbKeysComputed; scalar_t__ keys; } ;

/* Variables and functions */
 scalar_t__ xmlHashLookup (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 scalar_t__ xsltInitAllDocKeys (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltInitDocKeyTable (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

xmlNodeSetPtr
xsltGetKey(xsltTransformContextPtr ctxt, const xmlChar *name,
	   const xmlChar *nameURI, const xmlChar *value) {
    xmlNodeSetPtr ret;
    xsltKeyTablePtr table;
    int init_table = 0;

    if ((ctxt == NULL) || (name == NULL) || (value == NULL) ||
	(ctxt->document == NULL))
	return(NULL);

#ifdef WITH_XSLT_DEBUG_KEYS
    xsltGenericDebug(xsltGenericDebugContext,
	"Get key %s, value %s\n", name, value);
#endif

    /*
     * keys are computed only on-demand on first key access for a document
     */
    if ((ctxt->document->nbKeysComputed < ctxt->nbKeys) &&
        (ctxt->keyInitLevel == 0)) {
        /*
	 * If non-recursive behaviour, just try to initialize all keys
	 */
	if (xsltInitAllDocKeys(ctxt))
	    return(NULL);
    }

retry:
    table = (xsltKeyTablePtr) ctxt->document->keys;
    while (table != NULL) {
	if (((nameURI != NULL) == (table->nameURI != NULL)) &&
	    xmlStrEqual(table->name, name) &&
	    xmlStrEqual(table->nameURI, nameURI))
	{
	    ret = (xmlNodeSetPtr)xmlHashLookup(table->keys, value);
	    return(ret);
	}
	table = table->next;
    }

    if ((ctxt->keyInitLevel != 0) && (init_table == 0)) {
        /*
	 * Apparently one key is recursive and this one is needed,
	 * initialize just it, that time and retry
	 */
        xsltInitDocKeyTable(ctxt, name, nameURI);
	init_table = 1;
	goto retry;
    }

    return(NULL);
}