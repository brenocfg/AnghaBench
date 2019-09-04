#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ this_residual; int ptr; TYPE_4__* buffer; int /*<<< orphan*/  buffers_residual; } ;
struct scsi_cmnd {unsigned char* cmnd; TYPE_2__ SCp; TYPE_1__* device; } ;
struct TYPE_11__ {unsigned short base; unsigned long recon_tmo; } ;
typedef  TYPE_3__ ppa_struct ;
struct TYPE_12__ {scalar_t__ length; } ;
struct TYPE_9__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_BUS_BUSY ; 
 int /*<<< orphan*/  DID_ERROR ; 
 scalar_t__ PPA_BURST_SIZE ; 
 unsigned char READ_10 ; 
 unsigned char READ_6 ; 
 unsigned char WRITE_10 ; 
 unsigned char WRITE_6 ; 
 unsigned long jiffies ; 
 TYPE_3__* ppa_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppa_fail (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ppa_in (TYPE_3__*,int,int) ; 
 int ppa_out (TYPE_3__*,int,int) ; 
 int r_str (unsigned short) ; 
 int sg_virt (TYPE_4__*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ppa_completion(struct scsi_cmnd *cmd)
{
	/* Return codes:
	 * -1     Error
	 *  0     Told to schedule
	 *  1     Finished data transfer
	 */
	ppa_struct *dev = ppa_dev(cmd->device->host);
	unsigned short ppb = dev->base;
	unsigned long start_jiffies = jiffies;

	unsigned char r, v;
	int fast, bulk, status;

	v = cmd->cmnd[0];
	bulk = ((v == READ_6) ||
		(v == READ_10) || (v == WRITE_6) || (v == WRITE_10));

	/*
	 * We only get here if the drive is ready to comunicate,
	 * hence no need for a full ppa_wait.
	 */
	r = (r_str(ppb) & 0xf0);

	while (r != (unsigned char) 0xf0) {
		/*
		 * If we have been running for more than a full timer tick
		 * then take a rest.
		 */
		if (time_after(jiffies, start_jiffies + 1))
			return 0;

		if ((cmd->SCp.this_residual <= 0)) {
			ppa_fail(dev, DID_ERROR);
			return -1;	/* ERROR_RETURN */
		}

		/* On some hardware we have SCSI disconnected (6th bit low)
		 * for about 100usecs. It is too expensive to wait a 
		 * tick on every loop so we busy wait for no more than
		 * 500usecs to give the drive a chance first. We do not 
		 * change things for "normal" hardware since generally 
		 * the 6th bit is always high.
		 * This makes the CPU load higher on some hardware 
		 * but otherwise we can not get more than 50K/secs 
		 * on this problem hardware.
		 */
		if ((r & 0xc0) != 0xc0) {
			/* Wait for reconnection should be no more than 
			 * jiffy/2 = 5ms = 5000 loops
			 */
			unsigned long k = dev->recon_tmo;
			for (; k && ((r = (r_str(ppb) & 0xf0)) & 0xc0) != 0xc0;
			     k--)
				udelay(1);

			if (!k)
				return 0;
		}

		/* determine if we should use burst I/O */
		fast = (bulk && (cmd->SCp.this_residual >= PPA_BURST_SIZE))
		    ? PPA_BURST_SIZE : 1;

		if (r == (unsigned char) 0xc0)
			status = ppa_out(dev, cmd->SCp.ptr, fast);
		else
			status = ppa_in(dev, cmd->SCp.ptr, fast);

		cmd->SCp.ptr += fast;
		cmd->SCp.this_residual -= fast;

		if (!status) {
			ppa_fail(dev, DID_BUS_BUSY);
			return -1;	/* ERROR_RETURN */
		}
		if (cmd->SCp.buffer && !cmd->SCp.this_residual) {
			/* if scatter/gather, advance to the next segment */
			if (cmd->SCp.buffers_residual--) {
				cmd->SCp.buffer++;
				cmd->SCp.this_residual =
				    cmd->SCp.buffer->length;
				cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
			}
		}
		/* Now check to see if the drive is ready to comunicate */
		r = (r_str(ppb) & 0xf0);
		/* If not, drop back down to the scheduler and wait a timer tick */
		if (!(r & 0x80))
			return 0;
	}
	return 1;		/* FINISH_RETURN */
}