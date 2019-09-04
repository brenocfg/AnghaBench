#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nents; int /*<<< orphan*/ * sgl; } ;
struct TYPE_4__ {unsigned int length; TYPE_1__ table; } ;
struct scsi_cmnd {int sc_data_direction; TYPE_2__ sdb; } ;
struct isd200_info {int /*<<< orphan*/  sg; struct scsi_cmnd srb; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,void*,unsigned int) ; 

__attribute__((used)) static void isd200_set_srb(struct isd200_info *info,
	enum dma_data_direction dir, void* buff, unsigned bufflen)
{
	struct scsi_cmnd *srb = &info->srb;

	if (buff)
		sg_init_one(&info->sg, buff, bufflen);

	srb->sc_data_direction = dir;
	srb->sdb.table.sgl = buff ? &info->sg : NULL;
	srb->sdb.length = bufflen;
	srb->sdb.table.nents = buff ? 1 : 0;
}