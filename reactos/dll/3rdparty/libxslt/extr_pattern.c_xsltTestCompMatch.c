#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_28__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
struct TYPE_32__ {size_t nbstates; TYPE_28__* states; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ xsltStepStates ;
typedef  TYPE_4__* xsltStepOpPtr ;
typedef  TYPE_5__* xsltCompMatchPtr ;
typedef  TYPE_6__* xmlNodeSetPtr ;
typedef  TYPE_7__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_8__* xmlAttrPtr ;
struct TYPE_37__ {TYPE_7__* parent; } ;
struct TYPE_36__ {int type; char* name; TYPE_1__* ns; int /*<<< orphan*/  doc; struct TYPE_36__* parent; } ;
struct TYPE_35__ {int nodeNr; TYPE_7__** nodeTab; } ;
struct TYPE_34__ {int nbStep; int /*<<< orphan*/  nsNr; int /*<<< orphan*/  nsList; int /*<<< orphan*/  direct; TYPE_4__* steps; TYPE_7__* node; int /*<<< orphan*/  const* modeURI; int /*<<< orphan*/  const* mode; } ;
struct TYPE_33__ {int op; char* value; char* value2; int /*<<< orphan*/  value3; } ;
struct TYPE_31__ {TYPE_7__* inst; } ;
struct TYPE_30__ {int step; TYPE_7__* node; } ;
struct TYPE_29__ {char* href; } ;

/* Variables and functions */
 int XML_ATTRIBUTE_NODE ; 
#define  XML_CDATA_SECTION_NODE 147 
#define  XML_COMMENT_NODE 146 
 int XML_DOCB_DOCUMENT_NODE ; 
 int XML_DOCUMENT_NODE ; 
#define  XML_ELEMENT_NODE 145 
 int XML_HTML_DOCUMENT_NODE ; 
 int XML_NAMESPACE_DECL ; 
#define  XML_PI_NODE 144 
#define  XML_TEXT_NODE 143 
#define  XSLT_OP_ALL 142 
#define  XSLT_OP_ANCESTOR 141 
#define  XSLT_OP_ATTR 140 
#define  XSLT_OP_COMMENT 139 
#define  XSLT_OP_ELEM 138 
#define  XSLT_OP_END 137 
#define  XSLT_OP_ID 136 
#define  XSLT_OP_KEY 135 
#define  XSLT_OP_NODE 134 
#define  XSLT_OP_NS 133 
#define  XSLT_OP_PARENT 132 
#define  XSLT_OP_PI 131 
#define  XSLT_OP_PREDICATE 130 
#define  XSLT_OP_ROOT 129 
#define  XSLT_OP_TEXT 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xmlFree (TYPE_28__*) ; 
 TYPE_8__* xmlGetID (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlStrEqual (char*,char*) ; 
 TYPE_6__* xsltGetKey (TYPE_2__*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltPatPushState (TYPE_2__*,TYPE_3__*,int,TYPE_7__*) ; 
 int xsltTestCompMatchDirect (TYPE_2__*,TYPE_5__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltTestPredicateMatch (TYPE_2__*,TYPE_5__*,TYPE_7__*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,int /*<<< orphan*/ *,TYPE_7__*,char*) ; 

__attribute__((used)) static int
xsltTestCompMatch(xsltTransformContextPtr ctxt, xsltCompMatchPtr comp,
	          xmlNodePtr matchNode, const xmlChar *mode,
		  const xmlChar *modeURI) {
    int i;
    int found = 0;
    xmlNodePtr node = matchNode;
    xmlNodePtr oldInst;
    xsltStepOpPtr step, sel = NULL;
    xsltStepStates states = {0, 0, NULL}; /* // may require backtrack */

    if ((comp == NULL) || (node == NULL) || (ctxt == NULL)) {
	xsltTransformError(ctxt, NULL, node,
		"xsltTestCompMatch: null arg\n");
        return(-1);
    }
    if (mode != NULL) {
	if (comp->mode == NULL)
	    return(0);
	/*
	 * both mode strings must be interned on the stylesheet dictionary
	 */
	if (comp->mode != mode)
	    return(0);
    } else {
	if (comp->mode != NULL)
	    return(0);
    }
    if (modeURI != NULL) {
	if (comp->modeURI == NULL)
	    return(0);
	/*
	 * both modeURI strings must be interned on the stylesheet dictionary
	 */
	if (comp->modeURI != modeURI)
	    return(0);
    } else {
	if (comp->modeURI != NULL)
	    return(0);
    }

    /* Some XPath functions rely on inst being set correctly. */
    oldInst = ctxt->inst;
    ctxt->inst = comp->node;

    i = 0;
restart:
    for (;i < comp->nbStep;i++) {
	step = &comp->steps[i];
	if (step->op != XSLT_OP_PREDICATE)
	    sel = step;
	switch (step->op) {
            case XSLT_OP_END:
		goto found;
            case XSLT_OP_ROOT:
		if ((node->type == XML_DOCUMENT_NODE) ||
#ifdef LIBXML_DOCB_ENABLED
		    (node->type == XML_DOCB_DOCUMENT_NODE) ||
#endif
		    (node->type == XML_HTML_DOCUMENT_NODE))
		    continue;
		if ((node->type == XML_ELEMENT_NODE) && (node->name[0] == ' '))
		    continue;
		goto rollback;
            case XSLT_OP_ELEM:
		if (node->type != XML_ELEMENT_NODE)
		    goto rollback;
		if (step->value == NULL)
		    continue;
		if (step->value[0] != node->name[0])
		    goto rollback;
		if (!xmlStrEqual(step->value, node->name))
		    goto rollback;

		/* Namespace test */
		if (node->ns == NULL) {
		    if (step->value2 != NULL)
			goto rollback;
		} else if (node->ns->href != NULL) {
		    if (step->value2 == NULL)
			goto rollback;
		    if (!xmlStrEqual(step->value2, node->ns->href))
			goto rollback;
		}
		continue;
            case XSLT_OP_ATTR:
		if (node->type != XML_ATTRIBUTE_NODE)
		    goto rollback;
		if (step->value != NULL) {
		    if (step->value[0] != node->name[0])
			goto rollback;
		    if (!xmlStrEqual(step->value, node->name))
			goto rollback;
		}
		/* Namespace test */
		if (node->ns == NULL) {
		    if (step->value2 != NULL)
			goto rollback;
		} else if (step->value2 != NULL) {
		    if (!xmlStrEqual(step->value2, node->ns->href))
			goto rollback;
		}
		continue;
            case XSLT_OP_PARENT:
		if ((node->type == XML_DOCUMENT_NODE) ||
		    (node->type == XML_HTML_DOCUMENT_NODE) ||
#ifdef LIBXML_DOCB_ENABLED
		    (node->type == XML_DOCB_DOCUMENT_NODE) ||
#endif
		    (node->type == XML_NAMESPACE_DECL))
		    goto rollback;
		node = node->parent;
		if (node == NULL)
		    goto rollback;
		if (step->value == NULL)
		    continue;
		if (step->value[0] != node->name[0])
		    goto rollback;
		if (!xmlStrEqual(step->value, node->name))
		    goto rollback;
		/* Namespace test */
		if (node->ns == NULL) {
		    if (step->value2 != NULL)
			goto rollback;
		} else if (node->ns->href != NULL) {
		    if (step->value2 == NULL)
			goto rollback;
		    if (!xmlStrEqual(step->value2, node->ns->href))
			goto rollback;
		}
		continue;
            case XSLT_OP_ANCESTOR:
		/* TODO: implement coalescing of ANCESTOR/NODE ops */
		if (step->value == NULL) {
		    step = &comp->steps[i+1];
		    if (step->op == XSLT_OP_ROOT)
			goto found;
		    /* added NS, ID and KEY as a result of bug 168208 */
		    if ((step->op != XSLT_OP_ELEM) &&
			(step->op != XSLT_OP_ALL) &&
			(step->op != XSLT_OP_NS) &&
			(step->op != XSLT_OP_ID) &&
			(step->op != XSLT_OP_KEY))
			goto rollback;
		}
		if (node == NULL)
		    goto rollback;
		if ((node->type == XML_DOCUMENT_NODE) ||
		    (node->type == XML_HTML_DOCUMENT_NODE) ||
#ifdef LIBXML_DOCB_ENABLED
		    (node->type == XML_DOCB_DOCUMENT_NODE) ||
#endif
		    (node->type == XML_NAMESPACE_DECL))
		    goto rollback;
		node = node->parent;
		if ((step->op != XSLT_OP_ELEM) && step->op != XSLT_OP_ALL) {
		    xsltPatPushState(ctxt, &states, i, node);
		    continue;
		}
		i++;
		if (step->value == NULL) {
		    xsltPatPushState(ctxt, &states, i - 1, node);
		    continue;
		}
		while (node != NULL) {
		    if ((node->type == XML_ELEMENT_NODE) &&
			(step->value[0] == node->name[0]) &&
			(xmlStrEqual(step->value, node->name))) {
			/* Namespace test */
			if (node->ns == NULL) {
			    if (step->value2 == NULL)
				break;
			} else if (node->ns->href != NULL) {
			    if ((step->value2 != NULL) &&
			        (xmlStrEqual(step->value2, node->ns->href)))
				break;
			}
		    }
		    node = node->parent;
		}
		if (node == NULL)
		    goto rollback;
		xsltPatPushState(ctxt, &states, i - 1, node);
		continue;
            case XSLT_OP_ID: {
		/* TODO Handle IDs decently, must be done differently */
		xmlAttrPtr id;

		if (node->type != XML_ELEMENT_NODE)
		    goto rollback;

		id = xmlGetID(node->doc, step->value);
		if ((id == NULL) || (id->parent != node))
		    goto rollback;
		break;
	    }
            case XSLT_OP_KEY: {
		xmlNodeSetPtr list;
		int indx;

		list = xsltGetKey(ctxt, step->value,
			          step->value3, step->value2);
		if (list == NULL)
		    goto rollback;
		for (indx = 0;indx < list->nodeNr;indx++)
		    if (list->nodeTab[indx] == node)
			break;
		if (indx >= list->nodeNr)
		    goto rollback;
		break;
	    }
            case XSLT_OP_NS:
		if (node->type != XML_ELEMENT_NODE)
		    goto rollback;
		if (node->ns == NULL) {
		    if (step->value != NULL)
			goto rollback;
		} else if (node->ns->href != NULL) {
		    if (step->value == NULL)
			goto rollback;
		    if (!xmlStrEqual(step->value, node->ns->href))
			goto rollback;
		}
		break;
            case XSLT_OP_ALL:
		if (node->type != XML_ELEMENT_NODE)
		    goto rollback;
		break;
	    case XSLT_OP_PREDICATE: {
		/*
		 * When there is cascading XSLT_OP_PREDICATE or a predicate
		 * after an op which hasn't been optimized yet, then use a
		 * direct computation approach. It's not done directly
		 * at the beginning of the routine to filter out as much
		 * as possible this costly computation.
		 */
		if (comp->direct) {
		    found = xsltTestCompMatchDirect(ctxt, comp, matchNode,
						    comp->nsList, comp->nsNr);
                    goto exit;
		}

		if (!xsltTestPredicateMatch(ctxt, comp, node, step, sel))
		    goto rollback;

		break;
	    }
            case XSLT_OP_PI:
		if (node->type != XML_PI_NODE)
		    goto rollback;
		if (step->value != NULL) {
		    if (!xmlStrEqual(step->value, node->name))
			goto rollback;
		}
		break;
            case XSLT_OP_COMMENT:
		if (node->type != XML_COMMENT_NODE)
		    goto rollback;
		break;
            case XSLT_OP_TEXT:
		if ((node->type != XML_TEXT_NODE) &&
		    (node->type != XML_CDATA_SECTION_NODE))
		    goto rollback;
		break;
            case XSLT_OP_NODE:
		switch (node->type) {
		    case XML_ELEMENT_NODE:
		    case XML_CDATA_SECTION_NODE:
		    case XML_PI_NODE:
		    case XML_COMMENT_NODE:
		    case XML_TEXT_NODE:
			break;
		    default:
			goto rollback;
		}
		break;
	}
    }
found:
    found = 1;
exit:
    ctxt->inst = oldInst;
    if (states.states != NULL) {
        /* Free the rollback states */
	xmlFree(states.states);
    }
    return found;
rollback:
    /* got an error try to rollback */
    if (states.states == NULL || states.nbstates <= 0) {
        found = 0;
	goto exit;
    }
    states.nbstates--;
    i = states.states[states.nbstates].step;
    node = states.states[states.nbstates].node;
#if 0
    fprintf(stderr, "Pop: %d, %s\n", i, node->name);
#endif
    goto restart;
}