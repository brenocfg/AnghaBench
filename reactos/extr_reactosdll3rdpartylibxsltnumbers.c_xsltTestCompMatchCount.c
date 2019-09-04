#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  int /*<<< orphan*/ * xsltCompMatchPtr ;
typedef  TYPE_2__* xmlNodePtr ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__* ns; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  href; } ;

/* Variables and functions */
 scalar_t__ XML_NAMESPACE_DECL ; 
 int xmlStrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xsltTestCompMatchList (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xsltTestCompMatchCount(xsltTransformContextPtr context,
                       xmlNodePtr node,
                       xsltCompMatchPtr countPat,
                       xmlNodePtr cur)
{
    if (countPat != NULL) {
        return xsltTestCompMatchList(context, node, countPat);
    }
    else {
        /*
         * 7.7 Numbering
         *
         * If count attribute is not specified, then it defaults to the
         * pattern that matches any node with the same node type as the
         * current node and, if the current node has an expanded-name, with
         * the same expanded-name as the current node.
         */
        if (node->type != cur->type)
            return 0;
        if (node->type == XML_NAMESPACE_DECL)
            /*
             * Namespace nodes have no preceding siblings and no parents
             * that are namespace nodes. This means that node == cur.
             */
            return 1;
        /* TODO: Skip node types without expanded names like text nodes. */
        if (!xmlStrEqual(node->name, cur->name))
            return 0;
        if (node->ns == cur->ns)
            return 1;
        if ((node->ns == NULL) || (cur->ns == NULL))
            return 0;
        return (xmlStrEqual(node->ns->href, cur->ns->href));
    }
}