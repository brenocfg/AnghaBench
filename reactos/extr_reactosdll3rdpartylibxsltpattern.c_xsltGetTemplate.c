#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  int /*<<< orphan*/ * xsltTemplatePtr ;
typedef  TYPE_3__* xsltStylesheetPtr ;
typedef  TYPE_4__* xsltCompMatchPtr ;
typedef  TYPE_5__* xmlNodePtr ;
typedef  TYPE_6__* xmlDocPtr ;
typedef  char xmlChar ;
typedef  TYPE_7__* xmlAttrPtr ;
struct TYPE_24__ {int /*<<< orphan*/ * psvi; } ;
struct TYPE_23__ {int /*<<< orphan*/ * psvi; } ;
struct TYPE_22__ {int type; char* name; int /*<<< orphan*/ * psvi; } ;
struct TYPE_21__ {float priority; struct TYPE_21__* next; int /*<<< orphan*/ * template; } ;
struct TYPE_20__ {TYPE_4__* keyMatch; TYPE_4__* elemMatch; TYPE_4__* commentMatch; TYPE_4__* textMatch; TYPE_4__* rootMatch; TYPE_4__* piMatch; TYPE_4__* attrMatch; int /*<<< orphan*/ * templatesHash; } ;
struct TYPE_19__ {scalar_t__ nbKeys; TYPE_1__* document; scalar_t__ hasTemplKeyPatterns; int /*<<< orphan*/  modeURI; int /*<<< orphan*/  mode; TYPE_3__* style; } ;
struct TYPE_18__ {scalar_t__ nbKeysComputed; } ;

/* Variables and functions */
#define  XML_ATTRIBUTE_DECL 147 
#define  XML_ATTRIBUTE_NODE 146 
#define  XML_CDATA_SECTION_NODE 145 
#define  XML_COMMENT_NODE 144 
#define  XML_DOCUMENT_FRAG_NODE 143 
#define  XML_DOCUMENT_NODE 142 
#define  XML_DOCUMENT_TYPE_NODE 141 
#define  XML_DTD_NODE 140 
#define  XML_ELEMENT_DECL 139 
#define  XML_ELEMENT_NODE 138 
#define  XML_ENTITY_DECL 137 
#define  XML_ENTITY_NODE 136 
#define  XML_ENTITY_REF_NODE 135 
#define  XML_HTML_DOCUMENT_NODE 134 
#define  XML_NAMESPACE_DECL 133 
#define  XML_NOTATION_NODE 132 
#define  XML_PI_NODE 131 
#define  XML_TEXT_NODE 130 
#define  XML_XINCLUDE_END 129 
#define  XML_XINCLUDE_START 128 
 float XSLT_PAT_NO_PRIORITY ; 
 scalar_t__ xmlHashLookup3 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xsltComputeAllKeys (TYPE_2__*,TYPE_5__*) ; 
 TYPE_3__* xsltNextImport (TYPE_3__*) ; 
 scalar_t__ xsltTestCompMatch (TYPE_2__*,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

xsltTemplatePtr
xsltGetTemplate(xsltTransformContextPtr ctxt, xmlNodePtr node,
	        xsltStylesheetPtr style)
{
    xsltStylesheetPtr curstyle;
    xsltTemplatePtr ret = NULL;
    const xmlChar *name = NULL;
    xsltCompMatchPtr list = NULL;
    float priority;
    int keyed = 0;

    if ((ctxt == NULL) || (node == NULL))
	return(NULL);

    if (style == NULL) {
	curstyle = ctxt->style;
    } else {
	curstyle = xsltNextImport(style);
    }

    while ((curstyle != NULL) && (curstyle != style)) {
	priority = XSLT_PAT_NO_PRIORITY;
	/* TODO : handle IDs/keys here ! */
	if (curstyle->templatesHash != NULL) {
	    /*
	     * Use the top name as selector
	     */
	    switch (node->type) {
		case XML_ELEMENT_NODE:
		    if (node->name[0] == ' ')
			break;
		case XML_ATTRIBUTE_NODE:
		case XML_PI_NODE:
		    name = node->name;
		    break;
		case XML_DOCUMENT_NODE:
		case XML_HTML_DOCUMENT_NODE:
		case XML_TEXT_NODE:
		case XML_CDATA_SECTION_NODE:
		case XML_COMMENT_NODE:
		case XML_ENTITY_REF_NODE:
		case XML_ENTITY_NODE:
		case XML_DOCUMENT_TYPE_NODE:
		case XML_DOCUMENT_FRAG_NODE:
		case XML_NOTATION_NODE:
		case XML_DTD_NODE:
		case XML_ELEMENT_DECL:
		case XML_ATTRIBUTE_DECL:
		case XML_ENTITY_DECL:
		case XML_NAMESPACE_DECL:
		case XML_XINCLUDE_START:
		case XML_XINCLUDE_END:
		    break;
		default:
		    return(NULL);

	    }
	}
	if (name != NULL) {
	    /*
	     * find the list of applicable expressions based on the name
	     */
	    list = (xsltCompMatchPtr) xmlHashLookup3(curstyle->templatesHash,
					     name, ctxt->mode, ctxt->modeURI);
	} else
	    list = NULL;
	while (list != NULL) {
	    if (xsltTestCompMatch(ctxt, list, node,
			          ctxt->mode, ctxt->modeURI)) {
		ret = list->template;
		priority = list->priority;
		break;
	    }
	    list = list->next;
	}
	list = NULL;

	/*
	 * find alternate generic matches
	 */
	switch (node->type) {
	    case XML_ELEMENT_NODE:
		if (node->name[0] == ' ')
		    list = curstyle->rootMatch;
		else
		    list = curstyle->elemMatch;
		if (node->psvi != NULL) keyed = 1;
		break;
	    case XML_ATTRIBUTE_NODE: {
	        xmlAttrPtr attr;

		list = curstyle->attrMatch;
		attr = (xmlAttrPtr) node;
		if (attr->psvi != NULL) keyed = 1;
		break;
	    }
	    case XML_PI_NODE:
		list = curstyle->piMatch;
		if (node->psvi != NULL) keyed = 1;
		break;
	    case XML_DOCUMENT_NODE:
	    case XML_HTML_DOCUMENT_NODE: {
	        xmlDocPtr doc;

		list = curstyle->rootMatch;
		doc = (xmlDocPtr) node;
		if (doc->psvi != NULL) keyed = 1;
		break;
	    }
	    case XML_TEXT_NODE:
	    case XML_CDATA_SECTION_NODE:
		list = curstyle->textMatch;
		if (node->psvi != NULL) keyed = 1;
		break;
	    case XML_COMMENT_NODE:
		list = curstyle->commentMatch;
		if (node->psvi != NULL) keyed = 1;
		break;
	    case XML_ENTITY_REF_NODE:
	    case XML_ENTITY_NODE:
	    case XML_DOCUMENT_TYPE_NODE:
	    case XML_DOCUMENT_FRAG_NODE:
	    case XML_NOTATION_NODE:
	    case XML_DTD_NODE:
	    case XML_ELEMENT_DECL:
	    case XML_ATTRIBUTE_DECL:
	    case XML_ENTITY_DECL:
	    case XML_NAMESPACE_DECL:
	    case XML_XINCLUDE_START:
	    case XML_XINCLUDE_END:
		break;
	    default:
		break;
	}
	while ((list != NULL) &&
	       ((ret == NULL)  || (list->priority > priority))) {
	    if (xsltTestCompMatch(ctxt, list, node,
			          ctxt->mode, ctxt->modeURI)) {
		ret = list->template;
		priority = list->priority;
		break;
	    }
	    list = list->next;
	}
	/*
	 * Some of the tests for elements can also apply to documents
	 */
	if ((node->type == XML_DOCUMENT_NODE) ||
	    (node->type == XML_HTML_DOCUMENT_NODE) ||
	    (node->type == XML_TEXT_NODE)) {
	    list = curstyle->elemMatch;
	    while ((list != NULL) &&
		   ((ret == NULL)  || (list->priority > priority))) {
		if (xsltTestCompMatch(ctxt, list, node,
				      ctxt->mode, ctxt->modeURI)) {
		    ret = list->template;
		    priority = list->priority;
		    break;
		}
		list = list->next;
	    }
	} else if ((node->type == XML_PI_NODE) ||
		   (node->type == XML_COMMENT_NODE)) {
	    list = curstyle->elemMatch;
	    while ((list != NULL) &&
		   ((ret == NULL)  || (list->priority > priority))) {
		if (xsltTestCompMatch(ctxt, list, node,
				      ctxt->mode, ctxt->modeURI)) {
		    ret = list->template;
		    priority = list->priority;
		    break;
		}
		list = list->next;
	    }
	}

keyed_match:
	if (keyed) {
	    list = curstyle->keyMatch;
	    while ((list != NULL) &&
		   ((ret == NULL)  || (list->priority > priority))) {
		if (xsltTestCompMatch(ctxt, list, node,
				      ctxt->mode, ctxt->modeURI)) {
		    ret = list->template;
		    priority = list->priority;
		    break;
		}
		list = list->next;
	    }
	}
	else if (ctxt->hasTemplKeyPatterns &&
	    ((ctxt->document == NULL) ||
	     (ctxt->document->nbKeysComputed < ctxt->nbKeys)))
	{
	    /*
	    * Compute all remaining keys for this document.
	    *
	    * REVISIT TODO: I think this could be further optimized.
	    */
	    if (xsltComputeAllKeys(ctxt, node) == -1)
		goto error;

	    switch (node->type) {
		case XML_ELEMENT_NODE:
		    if (node->psvi != NULL) keyed = 1;
		    break;
		case XML_ATTRIBUTE_NODE:
		    if (((xmlAttrPtr) node)->psvi != NULL) keyed = 1;
		    break;
		case XML_TEXT_NODE:
		case XML_CDATA_SECTION_NODE:
		case XML_COMMENT_NODE:
		case XML_PI_NODE:
		    if (node->psvi != NULL) keyed = 1;
		    break;
		case XML_DOCUMENT_NODE:
		case XML_HTML_DOCUMENT_NODE:
		    if (((xmlDocPtr) node)->psvi != NULL) keyed = 1;
		    break;
		default:
		    break;
	    }
	    if (keyed)
		goto keyed_match;
	}
	if (ret != NULL)
	    return(ret);

	/*
	 * Cycle on next curstylesheet import.
	 */
	curstyle = xsltNextImport(curstyle);
    }

error:
    return(NULL);
}