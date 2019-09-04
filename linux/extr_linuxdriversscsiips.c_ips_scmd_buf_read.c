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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  scsi_sg_copy_to_buffer (struct scsi_cmnd*,void*,unsigned int) ; 

__attribute__((used)) static void
ips_scmd_buf_read(struct scsi_cmnd *scmd, void *data, unsigned int count)
{
	unsigned long flags;

	local_irq_save(flags);
	scsi_sg_copy_to_buffer(scmd, data, count);
	local_irq_restore(flags);
}