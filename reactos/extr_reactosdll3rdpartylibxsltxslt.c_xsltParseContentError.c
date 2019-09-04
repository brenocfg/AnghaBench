#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xmlNodePtr ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 scalar_t__ IS_XSLT_ELEM (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xsltParseContentError(xsltStylesheetPtr style,
		       xmlNodePtr node)
{
    if ((style == NULL) || (node == NULL))
	return;

    if (IS_XSLT_ELEM(node))
	xsltTransformError(NULL, style, node,
	    "The XSLT-element '%s' is not allowed at this position.\n",
	    node->name);
    else
	xsltTransformError(NULL, style, node,
	    "The element '%s' is not allowed at this position.\n",
	    node->name);
    style->errors++;
}