#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_11__ {int /*<<< orphan*/  bd_context; int /*<<< orphan*/  bd_index; TYPE_1__** bd_info; } ;
struct TYPE_10__ {scalar_t__ fn_oid; } ;
struct TYPE_9__ {int* extra_proc_missing; TYPE_3__* extra_procinfos; } ;
struct TYPE_8__ {scalar_t__ oi_opaque; } ;
typedef  TYPE_2__ InclusionOpaque ;
typedef  TYPE_3__ FmgrInfo ;
typedef  TYPE_4__ BrinDesc ;

/* Variables and functions */
 scalar_t__ InvalidOid ; 
 int PROCNUM_BASE ; 
 scalar_t__ RegProcedureIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info_copy (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getprocid (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  index_getprocinfo (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static FmgrInfo *
inclusion_get_procinfo(BrinDesc *bdesc, uint16 attno, uint16 procnum)
{
	InclusionOpaque *opaque;
	uint16		basenum = procnum - PROCNUM_BASE;

	/*
	 * We cache these in the opaque struct, to avoid repetitive syscache
	 * lookups.
	 */
	opaque = (InclusionOpaque *) bdesc->bd_info[attno - 1]->oi_opaque;

	/*
	 * If we already searched for this proc and didn't find it, don't bother
	 * searching again.
	 */
	if (opaque->extra_proc_missing[basenum])
		return NULL;

	if (opaque->extra_procinfos[basenum].fn_oid == InvalidOid)
	{
		if (RegProcedureIsValid(index_getprocid(bdesc->bd_index, attno,
												procnum)))
		{
			fmgr_info_copy(&opaque->extra_procinfos[basenum],
						   index_getprocinfo(bdesc->bd_index, attno, procnum),
						   bdesc->bd_context);
		}
		else
		{
			opaque->extra_proc_missing[basenum] = true;
			return NULL;
		}
	}

	return &opaque->extra_procinfos[basenum];
}