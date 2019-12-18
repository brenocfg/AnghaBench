#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  int /*<<< orphan*/ * xsltCompMatchPtr ;
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
struct TYPE_8__ {scalar_t__ type; struct TYPE_8__* parent; struct TYPE_8__* last; struct TYPE_8__* prev; } ;
struct TYPE_7__ {scalar_t__ next; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 scalar_t__ XML_DOCB_DOCUMENT_NODE ; 
 scalar_t__ XML_DOCUMENT_NODE ; 
 scalar_t__ XML_DTD_NODE ; 
 scalar_t__ XML_HTML_DOCUMENT_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 scalar_t__ XML_XINCLUDE_END ; 
 scalar_t__ XML_XINCLUDE_START ; 
 scalar_t__ xsltTestCompMatchCount (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ xsltTestCompMatchList (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xsltNumberFormatGetAnyLevel(xsltTransformContextPtr context,
			    xmlNodePtr node,
			    xsltCompMatchPtr countPat,
			    xsltCompMatchPtr fromPat,
			    double *array)
{
    int amount = 0;
    int cnt = 0;
    xmlNodePtr cur = node;

    while (cur != NULL) {
	/* process current node */
	if (xsltTestCompMatchCount(context, cur, countPat, node))
	    cnt++;
	if ((fromPat != NULL) &&
	    xsltTestCompMatchList(context, cur, fromPat)) {
	    break; /* while */
	}

	/* Skip to next preceding or ancestor */
	if ((cur->type == XML_DOCUMENT_NODE) ||
#ifdef LIBXML_DOCB_ENABLED
            (cur->type == XML_DOCB_DOCUMENT_NODE) ||
#endif
            (cur->type == XML_HTML_DOCUMENT_NODE))
	    break; /* while */

        if (cur->type == XML_NAMESPACE_DECL) {
            /*
            * The XPath module stores the parent of a namespace node in
            * the ns->next field.
            */
            cur = (xmlNodePtr) ((xmlNsPtr) cur)->next;
        } else if (cur->type == XML_ATTRIBUTE_NODE) {
            cur = cur->parent;
        } else {
            while ((cur->prev != NULL) && ((cur->prev->type == XML_DTD_NODE) ||
                   (cur->prev->type == XML_XINCLUDE_START) ||
                   (cur->prev->type == XML_XINCLUDE_END)))
                cur = cur->prev;
            if (cur->prev != NULL) {
                for (cur = cur->prev; cur->last != NULL; cur = cur->last);
            } else {
                cur = cur->parent;
            }
        }
    }

    array[amount++] = (double) cnt;

    return(amount);
}