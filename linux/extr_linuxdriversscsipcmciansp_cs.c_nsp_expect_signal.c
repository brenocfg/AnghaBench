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
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {unsigned int io_port; } ;

/* Variables and functions */
 unsigned char BUSMON_PHASE_MASK ; 
 int /*<<< orphan*/  IRQSTATUS ; 
 unsigned char IRQSTATUS_SCSI ; 
 int /*<<< orphan*/  SCSIBUSMON ; 
 unsigned char nsp_index_read (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned char nsp_read (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsp_expect_signal(struct scsi_cmnd *SCpnt,
			     unsigned char current_phase,
			     unsigned char mask)
{
	unsigned int  base	 = SCpnt->device->host->io_port;
	int	      time_out;
	unsigned char phase, i_src;

	//nsp_dbg(NSP_DEBUG_INTR, "current_phase=0x%x, mask=0x%x", current_phase, mask);

	time_out = 100;
	do {
		phase = nsp_index_read(base, SCSIBUSMON);
		if (phase == 0xff) {
			//nsp_dbg(NSP_DEBUG_INTR, "ret -1");
			return -1;
		}
		i_src = nsp_read(base, IRQSTATUS);
		if (i_src & IRQSTATUS_SCSI) {
			//nsp_dbg(NSP_DEBUG_INTR, "ret 0 found scsi signal");
			return 0;
		}
		if ((phase & mask) != 0 && (phase & BUSMON_PHASE_MASK) == current_phase) {
			//nsp_dbg(NSP_DEBUG_INTR, "ret 1 phase=0x%x", phase);
			return 1;
		}
	} while(time_out-- != 0);

	//nsp_dbg(NSP_DEBUG_INTR, "timeout");
	return -1;
}