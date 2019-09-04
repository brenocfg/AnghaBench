#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltUseAttrSetPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  const* ns; int /*<<< orphan*/  const* ncname; } ;

/* Variables and functions */
 TYPE_1__* xsltNewUseAttrSet (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static xsltUseAttrSetPtr
xsltAddUseAttrSetList(xsltUseAttrSetPtr list, const xmlChar *ncname,
                      const xmlChar *ns) {
    xsltUseAttrSetPtr next, cur;

    if (ncname == NULL)
        return(list);
    if (list == NULL)
	return(xsltNewUseAttrSet(ncname, ns));
    cur = list;
    while (cur != NULL) {
        if ((cur->ncname == ncname) && (cur->ns == ns))
            return(list);
	next = cur->next;
	if (next == NULL) {
	    cur->next = xsltNewUseAttrSet(ncname, ns);
	    return(list);
	}
	cur = next;
    }
    return(list);
}