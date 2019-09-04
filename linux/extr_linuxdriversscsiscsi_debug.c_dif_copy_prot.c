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
struct sg_mapping_iter {void* addr; int /*<<< orphan*/  length; } ;
struct scsi_cmnd {int dummy; } ;
typedef  size_t sector_t ;

/* Variables and functions */
 int SG_MITER_ATOMIC ; 
 int SG_MITER_FROM_SG ; 
 int SG_MITER_TO_SG ; 
 void* dif_store (size_t) ; 
 void* dif_storep ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 size_t min (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_prot_sglist (struct scsi_cmnd*) ; 
 int sdebug_store_sectors ; 
 scalar_t__ sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 

__attribute__((used)) static void dif_copy_prot(struct scsi_cmnd *SCpnt, sector_t sector,
			  unsigned int sectors, bool read)
{
	size_t resid;
	void *paddr;
	const void *dif_store_end = dif_storep + sdebug_store_sectors;
	struct sg_mapping_iter miter;

	/* Bytes of protection data to copy into sgl */
	resid = sectors * sizeof(*dif_storep);

	sg_miter_start(&miter, scsi_prot_sglist(SCpnt),
			scsi_prot_sg_count(SCpnt), SG_MITER_ATOMIC |
			(read ? SG_MITER_TO_SG : SG_MITER_FROM_SG));

	while (sg_miter_next(&miter) && resid > 0) {
		size_t len = min(miter.length, resid);
		void *start = dif_store(sector);
		size_t rest = 0;

		if (dif_store_end < start + len)
			rest = start + len - dif_store_end;

		paddr = miter.addr;

		if (read)
			memcpy(paddr, start, len - rest);
		else
			memcpy(start, paddr, len - rest);

		if (rest) {
			if (read)
				memcpy(paddr + len - rest, dif_storep, rest);
			else
				memcpy(dif_storep, paddr + len - rest, rest);
		}

		sector += len / sizeof(*dif_storep);
		resid -= len;
	}
	sg_miter_stop(&miter);
}