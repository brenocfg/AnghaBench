#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ (* PagePrecedes ) (int,int) ;} ;
typedef  TYPE_1__* SlruCtl ;

/* Variables and functions */
 int /*<<< orphan*/  SlruInternalDeleteSegment (TYPE_1__*,char*) ; 
 scalar_t__ stub1 (int,int) ; 

__attribute__((used)) static bool
SlruScanDirCbDeleteCutoff(SlruCtl ctl, char *filename, int segpage, void *data)
{
	int			cutoffPage = *(int *) data;

	if (ctl->PagePrecedes(segpage, cutoffPage))
		SlruInternalDeleteSegment(ctl, filename);

	return false;				/* keep going */
}