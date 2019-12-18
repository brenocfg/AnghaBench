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
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltAttrVTPtr ;
typedef  int /*<<< orphan*/  xsltAttrVT ;
struct TYPE_8__ {struct TYPE_8__* next; scalar_t__ strstart; int /*<<< orphan*/  max_seg; scalar_t__ nb_seg; } ;
struct TYPE_7__ {TYPE_2__* attVTs; int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_AVT_SEG ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static xsltAttrVTPtr
xsltNewAttrVT(xsltStylesheetPtr style) {
    xsltAttrVTPtr cur;

    cur = (xsltAttrVTPtr) xmlMalloc(sizeof(xsltAttrVT));
    if (cur == NULL) {
	xsltTransformError(NULL, style, NULL,
		"xsltNewAttrVTPtr : malloc failed\n");
	if (style != NULL) style->errors++;
	return(NULL);
    }
    memset(cur, 0, sizeof(xsltAttrVT));

    cur->nb_seg = 0;
    cur->max_seg = MAX_AVT_SEG;
    cur->strstart = 0;
    cur->next = style->attVTs;
    /*
     * Note: this pointer may be changed by a re-alloc within xsltCompileAttr,
     * so that code may change the stylesheet pointer also!
     */
    style->attVTs = (xsltAttrVTPtr) cur;

    return(cur);
}