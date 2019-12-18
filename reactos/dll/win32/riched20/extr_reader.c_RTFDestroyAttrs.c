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
struct TYPE_9__ {struct TYPE_9__* rtfSName; struct TYPE_9__* rtfSEText; struct TYPE_9__* rtfNextSE; struct TYPE_9__* rtfSSEList; struct TYPE_9__* rtfNextStyle; struct TYPE_9__* rtfNextColor; struct TYPE_9__* rtfFName; struct TYPE_9__* rtfNextFont; } ;
struct TYPE_8__ {TYPE_2__* styleList; TYPE_2__* colorList; TYPE_2__* fontList; } ;
typedef  TYPE_1__ RTF_Info ;
typedef  TYPE_2__ RTFStyleElt ;
typedef  TYPE_2__ RTFStyle ;
typedef  TYPE_2__ RTFFont ;
typedef  TYPE_2__ RTFColor ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 

__attribute__((used)) static void
RTFDestroyAttrs(RTF_Info *info)
{
	RTFColor	*cp;
	RTFFont		*fp;
	RTFStyle	*sp;
	RTFStyleElt	*eltList, *ep;

	while (info->fontList)
	{
		fp = info->fontList->rtfNextFont;
		heap_free (info->fontList->rtfFName);
		heap_free (info->fontList);
		info->fontList = fp;
	}
	while (info->colorList)
	{
		cp = info->colorList->rtfNextColor;
		heap_free (info->colorList);
		info->colorList = cp;
	}
	while (info->styleList)
	{
		sp = info->styleList->rtfNextStyle;
		eltList = info->styleList->rtfSSEList;
		while (eltList)
		{
			ep = eltList->rtfNextSE;
			heap_free (eltList->rtfSEText);
			heap_free (eltList);
			eltList = ep;
		}
		heap_free (info->styleList->rtfSName);
		heap_free (info->styleList);
		info->styleList = sp;
	}
}