#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_18__ ;
typedef  struct TYPE_36__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_3__* xsltTransformContextPtr ;
typedef  void* xsltDocumentPtr ;
typedef  TYPE_4__* xmlXPathParserContextPtr ;
typedef  TYPE_5__* xmlXPathObjectPtr ;
typedef  TYPE_6__* xmlXPathContextPtr ;
typedef  TYPE_7__* xmlNsPtr ;
typedef  TYPE_8__* xmlNodeSetPtr ;
typedef  TYPE_9__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_46__ {scalar_t__ type; TYPE_14__* doc; } ;
struct TYPE_45__ {int nodeNr; int /*<<< orphan*/ ** nodeTab; } ;
struct TYPE_44__ {TYPE_2__* next; } ;
struct TYPE_43__ {TYPE_9__* node; } ;
struct TYPE_42__ {scalar_t__ type; int /*<<< orphan*/ * stringval; TYPE_8__* nodesetval; } ;
struct TYPE_41__ {void* error; TYPE_1__* value; TYPE_6__* context; } ;
struct TYPE_40__ {TYPE_18__* document; void* state; int /*<<< orphan*/ * inst; } ;
struct TYPE_39__ {scalar_t__ type; } ;
struct TYPE_38__ {scalar_t__ type; } ;
struct TYPE_37__ {TYPE_14__* doc; } ;
struct TYPE_36__ {char* name; int /*<<< orphan*/ * _private; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 void* XPATH_INVALID_ARITY ; 
 void* XPATH_INVALID_TYPE ; 
 scalar_t__ XPATH_NODESET ; 
 scalar_t__ XPATH_STRING ; 
 scalar_t__ XPATH_XSLT_TREE ; 
 void* XSLT_STATE_STOPPED ; 
 TYPE_5__* valuePop (TYPE_4__*) ; 
 int /*<<< orphan*/  valuePush (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlSplitQName2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_5__*) ; 
 TYPE_5__* xmlXPathNewNodeSet (int /*<<< orphan*/ *) ; 
 TYPE_8__* xmlXPathNodeSetMerge (TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/ * xmlXPathNsLookup (TYPE_6__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* xmlXPathObjectCopy (TYPE_5__*) ; 
 int /*<<< orphan*/  xmlXPathStringFunction (TYPE_4__*,int) ; 
 TYPE_5__* xmlXPathWrapNodeSet (TYPE_8__*) ; 
 TYPE_18__* xsltFindDocument (TYPE_3__*,TYPE_14__*) ; 
 TYPE_8__* xsltGetKey (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xsltNewDocument (TYPE_3__*,TYPE_14__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 TYPE_3__* xsltXPathGetTransformContext (TYPE_4__*) ; 

void
xsltKeyFunction(xmlXPathParserContextPtr ctxt, int nargs){
    xmlXPathObjectPtr obj1, obj2;

    if (nargs != 2) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"key() : expects two arguments\n");
	ctxt->error = XPATH_INVALID_ARITY;
	return;
    }

    /*
    * Get the key's value.
    */
    obj2 = valuePop(ctxt);
    xmlXPathStringFunction(ctxt, 1);
    if ((obj2 == NULL) ||
	(ctxt->value == NULL) || (ctxt->value->type != XPATH_STRING)) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
	    "key() : invalid arg expecting a string\n");
	ctxt->error = XPATH_INVALID_TYPE;
	xmlXPathFreeObject(obj2);

	return;
    }
    /*
    * Get the key's name.
    */
    obj1 = valuePop(ctxt);

    if ((obj2->type == XPATH_NODESET) || (obj2->type == XPATH_XSLT_TREE)) {
	int i;
	xmlXPathObjectPtr newobj, ret;

	ret = xmlXPathNewNodeSet(NULL);

	if (obj2->nodesetval != NULL) {
	    for (i = 0; i < obj2->nodesetval->nodeNr; i++) {
		valuePush(ctxt, xmlXPathObjectCopy(obj1));
		valuePush(ctxt,
			  xmlXPathNewNodeSet(obj2->nodesetval->nodeTab[i]));
		xmlXPathStringFunction(ctxt, 1);
		xsltKeyFunction(ctxt, 2);
		newobj = valuePop(ctxt);
		ret->nodesetval = xmlXPathNodeSetMerge(ret->nodesetval,
						       newobj->nodesetval);
		xmlXPathFreeObject(newobj);
	    }
	}
	valuePush(ctxt, ret);
    } else {
	xmlNodeSetPtr nodelist = NULL;
	xmlChar *key = NULL, *value;
	const xmlChar *keyURI;
	xsltTransformContextPtr tctxt;
	xmlChar *qname, *prefix;
	xmlXPathContextPtr xpctxt = ctxt->context;
	xmlNodePtr tmpNode = NULL;
	xsltDocumentPtr oldDocInfo;

	tctxt = xsltXPathGetTransformContext(ctxt);

	oldDocInfo = tctxt->document;

	if (xpctxt->node == NULL) {
	    xsltTransformError(tctxt, NULL, tctxt->inst,
		"Internal error in xsltKeyFunction(): "
		"The context node is not set on the XPath context.\n");
	    tctxt->state = XSLT_STATE_STOPPED;
	    goto error;
	}
	/*
	 * Get the associated namespace URI if qualified name
	 */
	qname = obj1->stringval;
	key = xmlSplitQName2(qname, &prefix);
	if (key == NULL) {
	    key = xmlStrdup(obj1->stringval);
	    keyURI = NULL;
	    if (prefix != NULL)
		xmlFree(prefix);
	} else {
	    if (prefix != NULL) {
		keyURI = xmlXPathNsLookup(xpctxt, prefix);
		if (keyURI == NULL) {
		    xsltTransformError(tctxt, NULL, tctxt->inst,
			"key() : prefix %s is not bound\n", prefix);
		    /*
		    * TODO: Shouldn't we stop here?
		    */
		}
		xmlFree(prefix);
	    } else {
		keyURI = NULL;
	    }
	}

	/*
	 * Force conversion of first arg to string
	 */
	valuePush(ctxt, obj2);
	xmlXPathStringFunction(ctxt, 1);
	if ((ctxt->value == NULL) || (ctxt->value->type != XPATH_STRING)) {
	    xsltTransformError(tctxt, NULL, tctxt->inst,
		"key() : invalid arg expecting a string\n");
	    ctxt->error = XPATH_INVALID_TYPE;
	    goto error;
	}
	obj2 = valuePop(ctxt);
	value = obj2->stringval;

	/*
	* We need to ensure that ctxt->document is available for
	* xsltGetKey().
	* First find the relevant doc, which is the context node's
	* owner doc; using context->doc is not safe, since
	* the doc could have been acquired via the document() function,
	* or the doc might be a Result Tree Fragment.
	* FUTURE INFO: In XSLT 2.0 the key() function takes an additional
	* argument indicating the doc to use.
	*/
	if (xpctxt->node->type == XML_NAMESPACE_DECL) {
	    /*
	    * REVISIT: This is a libxml hack! Check xpath.c for details.
	    * The XPath module sets the owner element of a ns-node on
	    * the ns->next field.
	    */
	    if ((((xmlNsPtr) xpctxt->node)->next != NULL) &&
		(((xmlNsPtr) xpctxt->node)->next->type == XML_ELEMENT_NODE))
	    {
		tmpNode = (xmlNodePtr) ((xmlNsPtr) xpctxt->node)->next;
	    }
	} else
	    tmpNode = xpctxt->node;

	if ((tmpNode == NULL) || (tmpNode->doc == NULL)) {
	    xsltTransformError(tctxt, NULL, tctxt->inst,
		"Internal error in xsltKeyFunction(): "
		"Couldn't get the doc of the XPath context node.\n");
	    goto error;
	}

	if ((tctxt->document == NULL) ||
	    (tctxt->document->doc != tmpNode->doc))
	{
	    if (tmpNode->doc->name && (tmpNode->doc->name[0] == ' ')) {
		/*
		* This is a Result Tree Fragment.
		*/
		if (tmpNode->doc->_private == NULL) {
		    tmpNode->doc->_private = xsltNewDocument(tctxt, tmpNode->doc);
		    if (tmpNode->doc->_private == NULL)
			goto error;
		}
		tctxt->document = (xsltDocumentPtr) tmpNode->doc->_private;
	    } else {
		/*
		* May be the initial source doc or a doc acquired via the
		* document() function.
		*/
		tctxt->document = xsltFindDocument(tctxt, tmpNode->doc);
	    }
	    if (tctxt->document == NULL) {
		xsltTransformError(tctxt, NULL, tctxt->inst,
		    "Internal error in xsltKeyFunction(): "
		    "Could not get the document info of a context doc.\n");
		tctxt->state = XSLT_STATE_STOPPED;
		goto error;
	    }
	}
	/*
	* Get/compute the key value.
	*/
	nodelist = xsltGetKey(tctxt, key, keyURI, value);

error:
	tctxt->document = oldDocInfo;
	valuePush(ctxt, xmlXPathWrapNodeSet(
	    xmlXPathNodeSetMerge(NULL, nodelist)));
	if (key != NULL)
	    xmlFree(key);
    }

    if (obj1 != NULL)
	xmlXPathFreeObject(obj1);
    if (obj2 != NULL)
	xmlXPathFreeObject(obj2);
}