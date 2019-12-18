#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStackElemPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {TYPE_1__* comp; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ XSLT_FUNC_PARAM ; 
 scalar_t__ XSLT_FUNC_WITHPARAM ; 
 TYPE_2__* xsltStackLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
xsltCheckStackElem(xsltTransformContextPtr ctxt, const xmlChar *name,
	           const xmlChar *nameURI) {
    xsltStackElemPtr cur;

    if ((ctxt == NULL) || (name == NULL))
	return(-1);

    cur = xsltStackLookup(ctxt, name, nameURI);
    if (cur == NULL)
        return(0);
    if (cur->comp != NULL) {
        if (cur->comp->type == XSLT_FUNC_WITHPARAM)
	    return(3);
	else if (cur->comp->type == XSLT_FUNC_PARAM)
	    return(2);
    }

    return(1);
}