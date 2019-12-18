#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/ * xmlHashTablePtr ;
struct TYPE_3__ {int /*<<< orphan*/ * namedTemplates; int /*<<< orphan*/ * commentMatch; int /*<<< orphan*/ * piMatch; int /*<<< orphan*/ * textMatch; int /*<<< orphan*/ * parentMatch; int /*<<< orphan*/ * attrMatch; int /*<<< orphan*/ * elemMatch; int /*<<< orphan*/ * keyMatch; int /*<<< orphan*/ * rootMatch; int /*<<< orphan*/ * templatesHash; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlHashFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltFreeCompMatchList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xsltFreeCompMatchListEntry ; 

void
xsltFreeTemplateHashes(xsltStylesheetPtr style) {
    if (style->templatesHash != NULL)
	xmlHashFree((xmlHashTablePtr) style->templatesHash,
		    xsltFreeCompMatchListEntry);
    if (style->rootMatch != NULL)
        xsltFreeCompMatchList(style->rootMatch);
    if (style->keyMatch != NULL)
        xsltFreeCompMatchList(style->keyMatch);
    if (style->elemMatch != NULL)
        xsltFreeCompMatchList(style->elemMatch);
    if (style->attrMatch != NULL)
        xsltFreeCompMatchList(style->attrMatch);
    if (style->parentMatch != NULL)
        xsltFreeCompMatchList(style->parentMatch);
    if (style->textMatch != NULL)
        xsltFreeCompMatchList(style->textMatch);
    if (style->piMatch != NULL)
        xsltFreeCompMatchList(style->piMatch);
    if (style->commentMatch != NULL)
        xsltFreeCompMatchList(style->commentMatch);
    if (style->namedTemplates != NULL)
        xmlHashFree(style->namedTemplates, NULL);
}