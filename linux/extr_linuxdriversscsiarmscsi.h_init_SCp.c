#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_pointer {int dummy; } ;
struct TYPE_5__ {scalar_t__ phase; scalar_t__ this_residual; int /*<<< orphan*/ * ptr; TYPE_1__* buffer; scalar_t__ buffers_residual; } ;
struct scsi_cmnd {TYPE_3__ SCp; } ;
struct TYPE_4__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 TYPE_1__* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/ * sg_virt (TYPE_1__*) ; 

__attribute__((used)) static inline void init_SCp(struct scsi_cmnd *SCpnt)
{
	memset(&SCpnt->SCp, 0, sizeof(struct scsi_pointer));

	if (scsi_bufflen(SCpnt)) {
		unsigned long len = 0;

		SCpnt->SCp.buffer = scsi_sglist(SCpnt);
		SCpnt->SCp.buffers_residual = scsi_sg_count(SCpnt) - 1;
		SCpnt->SCp.ptr = sg_virt(SCpnt->SCp.buffer);
		SCpnt->SCp.this_residual = SCpnt->SCp.buffer->length;
		SCpnt->SCp.phase = scsi_bufflen(SCpnt);

#ifdef BELT_AND_BRACES
		{	/*
			 * Calculate correct buffer length.  Some commands
			 * come in with the wrong scsi_bufflen.
			 */
			struct scatterlist *sg;
			unsigned i, sg_count = scsi_sg_count(SCpnt);

			scsi_for_each_sg(SCpnt, sg, sg_count, i)
				len += sg->length;

			if (scsi_bufflen(SCpnt) != len) {
				printk(KERN_WARNING
				       "scsi%d.%c: bad request buffer "
				       "length %d, should be %ld\n",
					SCpnt->device->host->host_no,
					'0' + SCpnt->device->id,
					scsi_bufflen(SCpnt), len);
				/*
				 * FIXME: Totaly naive fixup. We should abort
				 * with error
				 */
				SCpnt->SCp.phase =
					min_t(unsigned long, len,
					      scsi_bufflen(SCpnt));
			}
		}
#endif
	} else {
		SCpnt->SCp.ptr = NULL;
		SCpnt->SCp.this_residual = 0;
		SCpnt->SCp.phase = 0;
	}
}