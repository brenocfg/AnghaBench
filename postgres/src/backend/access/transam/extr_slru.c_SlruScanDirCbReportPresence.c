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
struct TYPE_3__ {scalar_t__ (* PagePrecedes ) (int,int) ;} ;
typedef  TYPE_1__* SlruCtl ;

/* Variables and functions */
 int SLRU_PAGES_PER_SEGMENT ; 
 scalar_t__ stub1 (int,int) ; 

bool
SlruScanDirCbReportPresence(SlruCtl ctl, char *filename, int segpage, void *data)
{
	int			cutoffPage = *(int *) data;

	cutoffPage -= cutoffPage % SLRU_PAGES_PER_SEGMENT;

	if (ctl->PagePrecedes(segpage, cutoffPage))
		return true;			/* found one; don't iterate any more */

	return false;				/* keep going */
}