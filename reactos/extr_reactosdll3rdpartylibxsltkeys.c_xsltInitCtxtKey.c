#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltKeyTablePtr ;
typedef  TYPE_3__* xsltKeyDefPtr ;
typedef  TYPE_4__* xsltDocumentPtr ;
typedef  TYPE_5__* xmlXPathObjectPtr ;
typedef  TYPE_6__* xmlXPathContextPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  TYPE_7__* xmlNodeSetPtr ;
typedef  TYPE_8__* xmlNodePtr ;
typedef  TYPE_9__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_10__* xmlAttrPtr ;
struct TYPE_38__ {TYPE_3__* psvi; } ;
struct TYPE_37__ {int type; TYPE_3__* psvi; } ;
struct TYPE_36__ {int nodeNr; TYPE_8__** nodeTab; } ;
struct TYPE_35__ {int proximityPosition; int contextSize; int nsNr; int /*<<< orphan*/ * namespaces; TYPE_9__* doc; TYPE_8__* node; } ;
struct TYPE_34__ {scalar_t__ type; TYPE_7__* nodesetval; int /*<<< orphan*/ * stringval; } ;
struct TYPE_33__ {TYPE_2__* keys; TYPE_9__* doc; int /*<<< orphan*/  nbKeysComputed; } ;
struct TYPE_32__ {int nsNr; TYPE_8__* inst; int /*<<< orphan*/ * usecomp; int /*<<< orphan*/ * nameURI; int /*<<< orphan*/ * name; int /*<<< orphan*/ * comp; int /*<<< orphan*/ * nsList; } ;
struct TYPE_31__ {int /*<<< orphan*/  keys; struct TYPE_31__* next; int /*<<< orphan*/ * nameURI; int /*<<< orphan*/ * name; } ;
struct TYPE_30__ {scalar_t__ keyInitLevel; scalar_t__ nbKeys; TYPE_8__* inst; TYPE_4__* document; TYPE_8__* node; void* state; TYPE_6__* xpathCtxt; } ;
struct TYPE_29__ {TYPE_3__* psvi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_XSLT_REAL_NODE (TYPE_8__*) ; 
#define  XML_ATTRIBUTE_NODE 135 
#define  XML_CDATA_SECTION_NODE 134 
#define  XML_COMMENT_NODE 133 
#define  XML_DOCUMENT_NODE 132 
#define  XML_ELEMENT_NODE 131 
#define  XML_HTML_DOCUMENT_NODE 130 
#define  XML_PI_NODE 129 
#define  XML_TEXT_NODE 128 
 scalar_t__ XPATH_NODESET ; 
 scalar_t__ XPATH_STRING ; 
 void* XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlHashAddEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_7__* xmlHashLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlXPathCastNodeToString (TYPE_8__*) ; 
 int /*<<< orphan*/ * xmlXPathCastToString (TYPE_5__*) ; 
 TYPE_5__* xmlXPathCompiledEval (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_5__*) ; 
 int /*<<< orphan*/  xmlXPathNodeSetAdd (TYPE_7__*,TYPE_8__*) ; 
 TYPE_7__* xmlXPathNodeSetCreate (TYPE_8__*) ; 
 TYPE_2__* xsltNewKeyTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,TYPE_8__*,char*,...) ; 

int
xsltInitCtxtKey(xsltTransformContextPtr ctxt, xsltDocumentPtr idoc,
	        xsltKeyDefPtr keyDef)
{
    int i, len, k;
    xmlNodeSetPtr matchList = NULL, keylist;
    xmlXPathObjectPtr matchRes = NULL, useRes = NULL;
    xmlChar *str = NULL;
    xsltKeyTablePtr table;
    xmlNodePtr oldInst, cur;
    xmlNodePtr oldContextNode;
    xsltDocumentPtr oldDocInfo;
    int	oldXPPos, oldXPSize;
    xmlDocPtr oldXPDoc;
    int oldXPNsNr;
    xmlNsPtr *oldXPNamespaces;
    xmlXPathContextPtr xpctxt;

#ifdef KEY_INIT_DEBUG
fprintf(stderr, "xsltInitCtxtKey %s : %d\n", keyDef->name, ctxt->keyInitLevel);
#endif

    if ((keyDef->comp == NULL) || (keyDef->usecomp == NULL))
	return(-1);

    /*
     * Detect recursive keys
     */
    if (ctxt->keyInitLevel > ctxt->nbKeys) {
#ifdef WITH_XSLT_DEBUG_KEYS
	XSLT_TRACE(ctxt,XSLT_TRACE_KEYS,
	           xsltGenericDebug(xsltGenericDebugContext,
		       "xsltInitCtxtKey: key definition of %s is recursive\n",
		       keyDef->name));
#endif
	xsltTransformError(ctxt, NULL, keyDef->inst,
	    "Key definition for %s is recursive\n", keyDef->name);
	ctxt->state = XSLT_STATE_STOPPED;
        return(-1);
    }
    ctxt->keyInitLevel++;

    xpctxt = ctxt->xpathCtxt;
    idoc->nbKeysComputed++;
    /*
    * Save context state.
    */
    oldInst = ctxt->inst;
    oldDocInfo = ctxt->document;
    oldContextNode = ctxt->node;

    oldXPDoc = xpctxt->doc;
    oldXPPos = xpctxt->proximityPosition;
    oldXPSize = xpctxt->contextSize;
    oldXPNsNr = xpctxt->nsNr;
    oldXPNamespaces = xpctxt->namespaces;

    /*
    * Set up contexts.
    */
    ctxt->document = idoc;
    ctxt->node = (xmlNodePtr) idoc->doc;
    ctxt->inst = keyDef->inst;

    xpctxt->doc = idoc->doc;
    xpctxt->node = (xmlNodePtr) idoc->doc;
    /* TODO : clarify the use of namespaces in keys evaluation */
    xpctxt->namespaces = keyDef->nsList;
    xpctxt->nsNr = keyDef->nsNr;

    /*
    * Evaluate the 'match' expression of the xsl:key.
    * TODO: The 'match' is a *pattern*.
    */
    matchRes = xmlXPathCompiledEval(keyDef->comp, xpctxt);
    if (matchRes == NULL) {

#ifdef WITH_XSLT_DEBUG_KEYS
	XSLT_TRACE(ctxt,XSLT_TRACE_KEYS,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltInitCtxtKey: %s evaluation failed\n", keyDef->match));
#endif
	xsltTransformError(ctxt, NULL, keyDef->inst,
	    "Failed to evaluate the 'match' expression.\n");
	ctxt->state = XSLT_STATE_STOPPED;
	goto error;
    } else {
	if (matchRes->type == XPATH_NODESET) {
	    matchList = matchRes->nodesetval;

#ifdef WITH_XSLT_DEBUG_KEYS
	    if (matchList != NULL)
		XSLT_TRACE(ctxt,XSLT_TRACE_KEYS,xsltGenericDebug(xsltGenericDebugContext,
		     "xsltInitCtxtKey: %s evaluates to %d nodes\n",
				 keyDef->match, matchList->nodeNr));
#endif
	} else {
	    /*
	    * Is not a node set, but must be.
	    */
#ifdef WITH_XSLT_DEBUG_KEYS
	    XSLT_TRACE(ctxt,XSLT_TRACE_KEYS,xsltGenericDebug(xsltGenericDebugContext,
		 "xsltInitCtxtKey: %s is not a node set\n", keyDef->match));
#endif
	    xsltTransformError(ctxt, NULL, keyDef->inst,
		"The 'match' expression did not evaluate to a node set.\n");
	    ctxt->state = XSLT_STATE_STOPPED;
	    goto error;
	}
    }
    if ((matchList == NULL) || (matchList->nodeNr <= 0))
	goto exit;

    /**
     * Multiple key definitions for the same name are allowed, so
     * we must check if the key is already present for this doc
     */
    table = (xsltKeyTablePtr) idoc->keys;
    while (table != NULL) {
        if (xmlStrEqual(table->name, keyDef->name) &&
	    (((keyDef->nameURI == NULL) && (table->nameURI == NULL)) ||
	     ((keyDef->nameURI != NULL) && (table->nameURI != NULL) &&
	      (xmlStrEqual(table->nameURI, keyDef->nameURI)))))
	    break;
	table = table->next;
    }
    /**
     * If the key was not previously defined, create it now and
     * chain it to the list of keys for the doc
     */
    if (table == NULL) {
        table = xsltNewKeyTable(keyDef->name, keyDef->nameURI);
        if (table == NULL)
	    goto error;
        table->next = idoc->keys;
        idoc->keys = table;
    }

    /*
    * SPEC XSLT 1.0 (XSLT 2.0 does not clarify the context size!)
    * "...the use attribute of the xsl:key element is evaluated with x as
    "  the current node and with a node list containing just x as the
    *  current node list"
    */
    xpctxt->contextSize = 1;
    xpctxt->proximityPosition = 1;

    for (i = 0; i < matchList->nodeNr; i++) {
	cur = matchList->nodeTab[i];
	if (! IS_XSLT_REAL_NODE(cur))
	    continue;
        ctxt->node = cur;
	xpctxt->node = cur;
	/*
	* Process the 'use' of the xsl:key.
	* SPEC XSLT 1.0:
	* "The use attribute is an expression specifying the values of
	*  the key; the expression is evaluated once for each node that
	*  matches the pattern."
	*/
	if (useRes != NULL)
	    xmlXPathFreeObject(useRes);
	useRes = xmlXPathCompiledEval(keyDef->usecomp, xpctxt);
	if (useRes == NULL) {
	    xsltTransformError(ctxt, NULL, keyDef->inst,
		"Failed to evaluate the 'use' expression.\n");
	    ctxt->state = XSLT_STATE_STOPPED;
	    break;
	}
	if (useRes->type == XPATH_NODESET) {
	    if ((useRes->nodesetval != NULL) &&
		(useRes->nodesetval->nodeNr != 0))
	    {
		len = useRes->nodesetval->nodeNr;
		str = xmlXPathCastNodeToString(useRes->nodesetval->nodeTab[0]);
	    } else {
		continue;
	    }
	} else {
	    len = 1;
	    if (useRes->type == XPATH_STRING) {
		/*
		* Consume the string value.
		*/
		str = useRes->stringval;
		useRes->stringval = NULL;
	    } else {
		str = xmlXPathCastToString(useRes);
	    }
	}
	/*
	* Process all strings.
	*/
	k = 0;
	while (1) {
	    if (str == NULL)
		goto next_string;

#ifdef WITH_XSLT_DEBUG_KEYS
	    XSLT_TRACE(ctxt,XSLT_TRACE_KEYS,xsltGenericDebug(xsltGenericDebugContext,
		"xsl:key : node associated to ('%s', '%s')\n", keyDef->name, str));
#endif

	    keylist = xmlHashLookup(table->keys, str);
	    if (keylist == NULL) {
		keylist = xmlXPathNodeSetCreate(cur);
		if (keylist == NULL)
		    goto error;
		xmlHashAddEntry(table->keys, str, keylist);
	    } else {
		/*
		* TODO: How do we know if this function failed?
		*/
		xmlXPathNodeSetAdd(keylist, cur);
	    }
	    switch (cur->type) {
		case XML_ELEMENT_NODE:
		case XML_TEXT_NODE:
		case XML_CDATA_SECTION_NODE:
		case XML_PI_NODE:
		case XML_COMMENT_NODE:
		    cur->psvi = keyDef;
		    break;
		case XML_ATTRIBUTE_NODE:
		    ((xmlAttrPtr) cur)->psvi = keyDef;
		    break;
		case XML_DOCUMENT_NODE:
		case XML_HTML_DOCUMENT_NODE:
		    ((xmlDocPtr) cur)->psvi = keyDef;
		    break;
		default:
		    break;
	    }
	    xmlFree(str);
	    str = NULL;

next_string:
	    k++;
	    if (k >= len)
		break;
	    str = xmlXPathCastNodeToString(useRes->nodesetval->nodeTab[k]);
	}
    }

exit:
error:
    ctxt->keyInitLevel--;
    /*
    * Restore context state.
    */
    xpctxt->doc = oldXPDoc;
    xpctxt->nsNr = oldXPNsNr;
    xpctxt->namespaces = oldXPNamespaces;
    xpctxt->proximityPosition = oldXPPos;
    xpctxt->contextSize = oldXPSize;

    ctxt->node = oldContextNode;
    ctxt->document = oldDocInfo;
    ctxt->inst = oldInst;

    if (str)
	xmlFree(str);
    if (useRes != NULL)
	xmlXPathFreeObject(useRes);
    if (matchRes != NULL)
	xmlXPathFreeObject(matchRes);
    return(0);
}