#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_16__ ;

/* Type definitions */
typedef  TYPE_2__* xsltStylesheetPtr ;
typedef  TYPE_3__* xmlNsPtr ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_5__* xmlAttrPtr ;
struct TYPE_26__ {struct TYPE_26__* next; TYPE_4__* children; } ;
struct TYPE_25__ {scalar_t__ type; struct TYPE_25__* next; struct TYPE_25__* parent; struct TYPE_25__* children; TYPE_1__* ns; int /*<<< orphan*/ * content; TYPE_3__* nsDef; TYPE_16__* doc; TYPE_5__* properties; } ;
struct TYPE_24__ {struct TYPE_24__* next; int /*<<< orphan*/  href; int /*<<< orphan*/ * prefix; } ;
struct TYPE_23__ {scalar_t__ exclPrefixNr; scalar_t__ doc; int /*<<< orphan*/ * dict; int /*<<< orphan*/ * exclPrefixTab; scalar_t__ internalized; } ;
struct TYPE_22__ {int /*<<< orphan*/  href; } ;
struct TYPE_21__ {int /*<<< orphan*/ * dict; } ;

/* Variables and functions */
 scalar_t__ IS_BLANK_NODE (TYPE_4__*) ; 
 scalar_t__ IS_XSLT_ELEM (TYPE_4__*) ; 
 scalar_t__ IS_XSLT_NAME (TYPE_4__*,char*) ; 
 scalar_t__ XML_CDATA_SECTION_NODE ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_ENTITY_DECL ; 
 scalar_t__ XML_ENTITY_NODE ; 
 scalar_t__ XML_ENTITY_REF_NODE ; 
 scalar_t__ XML_TEXT_NODE ; 
 int /*<<< orphan*/  XSLT_NAMESPACE ; 
 int /*<<< orphan*/  exclPrefixPop (TYPE_2__*) ; 
 scalar_t__ xmlDictLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlDictOwns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* xmlDocGetRootElement (TYPE_16__*) ; 
 int /*<<< orphan*/  xmlFreeNode (TYPE_4__*) ; 
 int xmlNodeGetSpacePreserve (TYPE_4__*) ; 
 int /*<<< orphan*/  xmlNodeSetContent (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlUnlinkNode (TYPE_4__*) ; 
 int /*<<< orphan*/  xsltCheckExtURI (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int xsltParseStylesheetExcludePrefix (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xsltPreprocessStylesheet(xsltStylesheetPtr style, xmlNodePtr cur)
{
    xmlNodePtr deleteNode, styleelem;
    int internalize = 0;

    if ((style == NULL) || (cur == NULL))
        return;

    if ((cur->doc != NULL) && (style->dict != NULL) &&
        (cur->doc->dict == style->dict))
	internalize = 1;
    else
        style->internalized = 0;

    if ((cur != NULL) && (IS_XSLT_ELEM(cur)) &&
        (IS_XSLT_NAME(cur, "stylesheet"))) {
	styleelem = cur;
    } else {
        styleelem = NULL;
    }

    /*
     * This content comes from the stylesheet
     * For stylesheets, the set of whitespace-preserving
     * element names consists of just xsl:text.
     */
    deleteNode = NULL;
    while (cur != NULL) {
	if (deleteNode != NULL) {
#ifdef WITH_XSLT_DEBUG_BLANKS
	    xsltGenericDebug(xsltGenericDebugContext,
	     "xsltPreprocessStylesheet: removing ignorable blank node\n");
#endif
	    xmlUnlinkNode(deleteNode);
	    xmlFreeNode(deleteNode);
	    deleteNode = NULL;
	}
	if (cur->type == XML_ELEMENT_NODE) {
	    int exclPrefixes;
	    /*
	     * Internalize attributes values.
	     */
	    if ((internalize) && (cur->properties != NULL)) {
	        xmlAttrPtr attr = cur->properties;
		xmlNodePtr txt;

		while (attr != NULL) {
		    txt = attr->children;
		    if ((txt != NULL) && (txt->type == XML_TEXT_NODE) &&
		        (txt->content != NULL) &&
			(!xmlDictOwns(style->dict, txt->content)))
		    {
			xmlChar *tmp;

			/*
			 * internalize the text string, goal is to speed
			 * up operations and minimize used space by compiled
			 * stylesheets.
			 */
			tmp = (xmlChar *) xmlDictLookup(style->dict,
			                                txt->content, -1);
			if (tmp != txt->content) {
			    xmlNodeSetContent(txt, NULL);
			    txt->content = tmp;
			}
		    }
		    attr = attr->next;
		}
	    }
	    if (IS_XSLT_ELEM(cur)) {
		exclPrefixes = 0;
		if (IS_XSLT_NAME(cur, "text")) {
		    for (;exclPrefixes > 0;exclPrefixes--)
			exclPrefixPop(style);
		    goto skip_children;
		}
	    } else {
		exclPrefixes = xsltParseStylesheetExcludePrefix(style, cur, 0);
	    }

	    if ((cur->nsDef != NULL) && (style->exclPrefixNr > 0)) {
		xmlNsPtr ns = cur->nsDef, prev = NULL, next;
		xmlNodePtr root = NULL;
		int i, moved;

		root = xmlDocGetRootElement(cur->doc);
		if ((root != NULL) && (root != cur)) {
		    while (ns != NULL) {
			moved = 0;
			next = ns->next;
			for (i = 0;i < style->exclPrefixNr;i++) {
			    if ((ns->prefix != NULL) &&
			        (xmlStrEqual(ns->href,
					     style->exclPrefixTab[i]))) {
				/*
				 * Move the namespace definition on the root
				 * element to avoid duplicating it without
				 * loosing it.
				 */
				if (prev == NULL) {
				    cur->nsDef = ns->next;
				} else {
				    prev->next = ns->next;
				}
				ns->next = root->nsDef;
				root->nsDef = ns;
				moved = 1;
				break;
			    }
			}
			if (moved == 0)
			    prev = ns;
			ns = next;
		    }
		}
	    }
	    /*
	     * If we have prefixes locally, recurse and pop them up when
	     * going back
	     */
	    if (exclPrefixes > 0) {
		xsltPreprocessStylesheet(style, cur->children);
		for (;exclPrefixes > 0;exclPrefixes--)
		    exclPrefixPop(style);
		goto skip_children;
	    }
	} else if (cur->type == XML_TEXT_NODE) {
	    if (IS_BLANK_NODE(cur)) {
		if (xmlNodeGetSpacePreserve(cur->parent) != 1) {
		    deleteNode = cur;
		}
	    } else if ((cur->content != NULL) && (internalize) &&
	               (!xmlDictOwns(style->dict, cur->content))) {
		xmlChar *tmp;

		/*
		 * internalize the text string, goal is to speed
		 * up operations and minimize used space by compiled
		 * stylesheets.
		 */
		tmp = (xmlChar *) xmlDictLookup(style->dict, cur->content, -1);
		xmlNodeSetContent(cur, NULL);
		cur->content = tmp;
	    }
	} else if ((cur->type != XML_ELEMENT_NODE) &&
		   (cur->type != XML_CDATA_SECTION_NODE)) {
	    deleteNode = cur;
	    goto skip_children;
	}

	/*
	 * Skip to next node. In case of a namespaced element children of
	 * the stylesheet and not in the XSLT namespace and not an extension
	 * element, ignore its content.
	 */
	if ((cur->type == XML_ELEMENT_NODE) && (cur->ns != NULL) &&
	    (styleelem != NULL) && (cur->parent == styleelem) &&
	    (!xmlStrEqual(cur->ns->href, XSLT_NAMESPACE)) &&
	    (!xsltCheckExtURI(style, cur->ns->href))) {
	    goto skip_children;
	} else if (cur->children != NULL) {
	    if ((cur->children->type != XML_ENTITY_DECL) &&
		(cur->children->type != XML_ENTITY_REF_NODE) &&
		(cur->children->type != XML_ENTITY_NODE)) {
		cur = cur->children;
		continue;
	    }
	}

skip_children:
	if (cur->next != NULL) {
	    cur = cur->next;
	    continue;
	}
	do {

	    cur = cur->parent;
	    if (cur == NULL)
		break;
	    if (cur == (xmlNodePtr) style->doc) {
		cur = NULL;
		break;
	    }
	    if (cur->next != NULL) {
		cur = cur->next;
		break;
	    }
	} while (cur != NULL);
    }
    if (deleteNode != NULL) {
#ifdef WITH_XSLT_DEBUG_PARSING
	xsltGenericDebug(xsltGenericDebugContext,
	 "xsltPreprocessStylesheet: removing ignorable blank node\n");
#endif
	xmlUnlinkNode(deleteNode);
	xmlFreeNode(deleteNode);
    }
}