#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTemplatePtr ;
typedef  TYPE_2__* xsltStylesheetPtr ;
typedef  TYPE_3__* xmlNsPtr ;
typedef  TYPE_4__* xmlNodePtr ;
struct TYPE_13__ {scalar_t__ type; struct TYPE_13__* parent; TYPE_3__* nsDef; } ;
struct TYPE_12__ {struct TYPE_12__* next; int /*<<< orphan*/ * prefix; int /*<<< orphan*/ * href; } ;
struct TYPE_11__ {int exclPrefixNr; int /*<<< orphan*/ ** exclPrefixTab; } ;
struct TYPE_10__ {int inheritedNsNr; TYPE_3__** inheritedNs; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/ * XSLT_NAMESPACE ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__ xmlRealloc (TYPE_3__**,int) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xsltCheckExtPrefix (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 

__attribute__((used)) static int
xsltGetInheritedNsList(xsltStylesheetPtr style,
	               xsltTemplatePtr template,
	               xmlNodePtr node)
{
    xmlNsPtr cur;
    xmlNsPtr *ret = NULL;
    int nbns = 0;
    int maxns = 10;
    int i;

    if ((style == NULL) || (template == NULL) || (node == NULL) ||
	(template->inheritedNsNr != 0) || (template->inheritedNs != NULL))
	return(0);
    while (node != NULL) {
        if (node->type == XML_ELEMENT_NODE) {
            cur = node->nsDef;
            while (cur != NULL) {
		if (xmlStrEqual(cur->href, XSLT_NAMESPACE))
		    goto skip_ns;

		if ((cur->prefix != NULL) &&
		    (xsltCheckExtPrefix(style, cur->prefix)))
		    goto skip_ns;
		/*
		* Check if this namespace was excluded.
		* Note that at this point only the exclusions defined
		* on the topmost stylesheet element are in the exclusion-list.
		*/
		for (i = 0;i < style->exclPrefixNr;i++) {
		    if (xmlStrEqual(cur->href, style->exclPrefixTab[i]))
			goto skip_ns;
		}
                if (ret == NULL) {
                    ret =
                        (xmlNsPtr *) xmlMalloc((maxns + 1) *
                                               sizeof(xmlNsPtr));
                    if (ret == NULL) {
                        xmlGenericError(xmlGenericErrorContext,
                                        "xsltGetInheritedNsList : out of memory!\n");
                        return(0);
                    }
                    ret[nbns] = NULL;
                }
		/*
		* Skip shadowed namespace bindings.
		*/
                for (i = 0; i < nbns; i++) {
                    if ((cur->prefix == ret[i]->prefix) ||
                        (xmlStrEqual(cur->prefix, ret[i]->prefix)))
                        break;
                }
                if (i >= nbns) {
                    if (nbns >= maxns) {
                        maxns *= 2;
                        ret = (xmlNsPtr *) xmlRealloc(ret,
                                                      (maxns +
                                                       1) *
                                                      sizeof(xmlNsPtr));
                        if (ret == NULL) {
                            xmlGenericError(xmlGenericErrorContext,
                                            "xsltGetInheritedNsList : realloc failed!\n");
                            return(0);
                        }
                    }
                    ret[nbns++] = cur;
                    ret[nbns] = NULL;
                }
skip_ns:
                cur = cur->next;
            }
        }
        node = node->parent;
    }
    if (nbns != 0) {
#ifdef WITH_XSLT_DEBUG_PARSING
        xsltGenericDebug(xsltGenericDebugContext,
                         "template has %d inherited namespaces\n", nbns);
#endif
	template->inheritedNsNr = nbns;
	template->inheritedNs = ret;
    }
    return (nbns);
}