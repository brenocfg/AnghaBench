#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * fn_extra; int /*<<< orphan*/  fn_mcxt; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

void
fmgr_info_copy(FmgrInfo *dstinfo, FmgrInfo *srcinfo,
			   MemoryContext destcxt)
{
	memcpy(dstinfo, srcinfo, sizeof(FmgrInfo));
	dstinfo->fn_mcxt = destcxt;
	dstinfo->fn_extra = NULL;
}