#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformFunction ;
typedef  int /*<<< orphan*/  xsltStylesheetPtr ;
typedef  int /*<<< orphan*/ * xsltElemPreCompPtr ;
typedef  int /*<<< orphan*/  xsltElemPreComp ;
typedef  int /*<<< orphan*/  xmlNodePtr ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xsltFreeElemPreComp ; 
 int /*<<< orphan*/  xsltInitElemPreComp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

xsltElemPreCompPtr
xsltNewElemPreComp(xsltStylesheetPtr style, xmlNodePtr inst,
                   xsltTransformFunction function)
{
    xsltElemPreCompPtr cur;

    cur = (xsltElemPreCompPtr) xmlMalloc(sizeof(xsltElemPreComp));
    if (cur == NULL) {
        xsltTransformError(NULL, style, NULL,
                           "xsltNewExtElement : malloc failed\n");
        return (NULL);
    }
    memset(cur, 0, sizeof(xsltElemPreComp));

    xsltInitElemPreComp(cur, style, inst, function, xsltFreeElemPreComp);

    return (cur);
}