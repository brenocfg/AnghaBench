#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStackElemPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  const* nameURI; int /*<<< orphan*/  const* name; } ;
struct TYPE_5__ {int varsNr; int varsBase; TYPE_2__** varsTab; int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  stack_addr ; 
 int /*<<< orphan*/  stack_cmp ; 
 int /*<<< orphan*/ * xmlDictLookup (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static xsltStackElemPtr
xsltStackLookup(xsltTransformContextPtr ctxt, const xmlChar *name,
	        const xmlChar *nameURI) {
    int i;
    xsltStackElemPtr cur;

    if ((ctxt == NULL) || (name == NULL) || (ctxt->varsNr == 0))
	return(NULL);

    /*
     * Do the lookup from the top of the stack, but
     * don't use params being computed in a call-param
     * First lookup expects the variable name and URI to
     * come from the disctionnary and hence pointer comparison.
     */
    for (i = ctxt->varsNr; i > ctxt->varsBase; i--) {
	cur = ctxt->varsTab[i-1];
	while (cur != NULL) {
	    if ((cur->name == name) && (cur->nameURI == nameURI)) {
#if 0
		stack_addr++;
#endif
		return(cur);
	    }
	    cur = cur->next;
	}
    }

    /*
     * Redo the lookup with interned string compares
     * to avoid string compares.
     */
    name = xmlDictLookup(ctxt->dict, name, -1);
    if (nameURI != NULL)
        nameURI = xmlDictLookup(ctxt->dict, nameURI, -1);

    for (i = ctxt->varsNr; i > ctxt->varsBase; i--) {
	cur = ctxt->varsTab[i-1];
	while (cur != NULL) {
	    if ((cur->name == name) && (cur->nameURI == nameURI)) {
#if 0
		stack_cmp++;
#endif
		return(cur);
	    }
	    cur = cur->next;
	}
    }

    return(NULL);
}