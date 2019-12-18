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
struct TYPE_4__ {int earliestExistingPage; } ;
typedef  TYPE_1__ mxtruncinfo ;
struct TYPE_5__ {scalar_t__ (* PagePrecedes ) (int,int) ;} ;
typedef  TYPE_2__* SlruCtl ;

/* Variables and functions */
 scalar_t__ stub1 (int,int) ; 

__attribute__((used)) static bool
SlruScanDirCbFindEarliest(SlruCtl ctl, char *filename, int segpage, void *data)
{
	mxtruncinfo *trunc = (mxtruncinfo *) data;

	if (trunc->earliestExistingPage == -1 ||
		ctl->PagePrecedes(segpage, trunc->earliestExistingPage))
	{
		trunc->earliestExistingPage = segpage;
	}

	return false;				/* keep going */
}