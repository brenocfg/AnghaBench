#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int this_residual; int /*<<< orphan*/  ptr; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; TYPE_1__ SCp; } ;
struct NCR5380_hostdata {int dummy; } ;

/* Variables and functions */
#define  CMD_MODE_UNKNOWN 130 
#define  CMD_SURELY_BLOCK_MODE 129 
#define  CMD_SURELY_BYTE_MODE 128 
 int DMA_MIN_SIZE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 scalar_t__ IS_A_TT () ; 
 int /*<<< orphan*/  NDEBUG_DMA ; 
 int /*<<< orphan*/  STRAM_ADDR (int /*<<< orphan*/ ) ; 
 int STRAM_BUFFER_SIZE ; 
 scalar_t__ atari_dma_buffer ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int,int) ; 
 int falcon_classify_cmd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atari_scsi_dma_xfer_len(struct NCR5380_hostdata *hostdata,
                                   struct scsi_cmnd *cmd)
{
	int wanted_len = cmd->SCp.this_residual;
	int possible_len, limit;

	if (wanted_len < DMA_MIN_SIZE)
		return 0;

	if (IS_A_TT())
		/* TT SCSI DMA can transfer arbitrary #bytes */
		return wanted_len;

	/* ST DMA chip is stupid -- only multiples of 512 bytes! (and max.
	 * 255*512 bytes, but this should be enough)
	 *
	 * ++roman: Aaargl! Another Falcon-SCSI problem... There are some commands
	 * that return a number of bytes which cannot be known beforehand. In this
	 * case, the given transfer length is an "allocation length". Now it
	 * can happen that this allocation length is a multiple of 512 bytes and
	 * the DMA is used. But if not n*512 bytes really arrive, some input data
	 * will be lost in the ST-DMA's FIFO :-( Thus, we have to distinguish
	 * between commands that do block transfers and those that do byte
	 * transfers. But this isn't easy... there are lots of vendor specific
	 * commands, and the user can issue any command via the
	 * SCSI_IOCTL_SEND_COMMAND.
	 *
	 * The solution: We classify SCSI commands in 1) surely block-mode cmd.s,
	 * 2) surely byte-mode cmd.s and 3) cmd.s with unknown mode. In case 1)
	 * and 3), the thing to do is obvious: allow any number of blocks via DMA
	 * or none. In case 2), we apply some heuristic: Byte mode is assumed if
	 * the transfer (allocation) length is < 1024, hoping that no cmd. not
	 * explicitly known as byte mode have such big allocation lengths...
	 * BTW, all the discussion above applies only to reads. DMA writes are
	 * unproblematic anyways, since the targets aborts the transfer after
	 * receiving a sufficient number of bytes.
	 *
	 * Another point: If the transfer is from/to an non-ST-RAM address, we
	 * use the dribble buffer and thus can do only STRAM_BUFFER_SIZE bytes.
	 */

	if (cmd->sc_data_direction == DMA_TO_DEVICE) {
		/* Write operation can always use the DMA, but the transfer size must
		 * be rounded up to the next multiple of 512 (atari_dma_setup() does
		 * this).
		 */
		possible_len = wanted_len;
	} else {
		/* Read operations: if the wanted transfer length is not a multiple of
		 * 512, we cannot use DMA, since the ST-DMA cannot split transfers
		 * (no interrupt on DMA finished!)
		 */
		if (wanted_len & 0x1ff)
			possible_len = 0;
		else {
			/* Now classify the command (see above) and decide whether it is
			 * allowed to do DMA at all */
			switch (falcon_classify_cmd(cmd)) {
			case CMD_SURELY_BLOCK_MODE:
				possible_len = wanted_len;
				break;
			case CMD_SURELY_BYTE_MODE:
				possible_len = 0; /* DMA prohibited */
				break;
			case CMD_MODE_UNKNOWN:
			default:
				/* For unknown commands assume block transfers if the transfer
				 * size/allocation length is >= 1024 */
				possible_len = (wanted_len < 1024) ? 0 : wanted_len;
				break;
			}
		}
	}

	/* Last step: apply the hard limit on DMA transfers */
	limit = (atari_dma_buffer && !STRAM_ADDR(virt_to_phys(cmd->SCp.ptr))) ?
		    STRAM_BUFFER_SIZE : 255*512;
	if (possible_len > limit)
		possible_len = limit;

	if (possible_len != wanted_len)
		dprintk(NDEBUG_DMA, "DMA transfer now %d bytes instead of %d\n",
		        possible_len, wanted_len);

	return possible_len;
}