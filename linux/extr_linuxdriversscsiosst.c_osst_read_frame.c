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
struct osst_tape {scalar_t__ first_frame_position; scalar_t__ read_error_frame; TYPE_1__* buffer; int /*<<< orphan*/  timeout; scalar_t__ poll; } ;
struct osst_request {int dummy; } ;
struct TYPE_2__ {scalar_t__ syscall_result; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EBUSY ; 
 int MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 int /*<<< orphan*/  OS_FRAME_SIZE ; 
 unsigned char READ_6 ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct osst_request* osst_do_scsi (struct osst_request*,struct osst_tape*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int osst_recover_wait_frame (struct osst_tape*,struct osst_request**,int /*<<< orphan*/ ) ; 
 scalar_t__ osst_wait_frame (struct osst_tape*,struct osst_request**,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int osst_read_frame(struct osst_tape * STp, struct osst_request ** aSRpnt, int timeout)
{
	unsigned char		cmd[MAX_COMMAND_SIZE];
	struct osst_request   * SRpnt;
	int			retval = 0;
#if DEBUG
	os_aux_t	      * aux    = STp->buffer->aux;
	char		      * name   = tape_name(STp);
#endif

	if (STp->poll)
		if (osst_wait_frame (STp, aSRpnt, STp->first_frame_position, 0, timeout))
			retval = osst_recover_wait_frame(STp, aSRpnt, 0);

	memset(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = READ_6;
	cmd[1] = 1;
	cmd[4] = 1;

#if DEBUG
	if (debugging)
		printk(OSST_DEB_MSG "%s:D: Reading frame from OnStream tape\n", name);
#endif
	SRpnt = osst_do_scsi(*aSRpnt, STp, cmd, OS_FRAME_SIZE, DMA_FROM_DEVICE,
				      STp->timeout, MAX_RETRIES, 1);
	*aSRpnt = SRpnt;
	if (!SRpnt)
		return (-EBUSY);

	if ((STp->buffer)->syscall_result) {
	    retval = 1;
	    if (STp->read_error_frame == 0) {
		STp->read_error_frame = STp->first_frame_position;
#if DEBUG
		printk(OSST_DEB_MSG "%s:D: Recording read error at %d\n", name, STp->read_error_frame);
#endif
	    }
#if DEBUG
	    if (debugging)
		printk(OSST_DEB_MSG "%s:D: Sense: %2x %2x %2x %2x %2x %2x %2x %2x\n",
		   name,
		   SRpnt->sense[0], SRpnt->sense[1],
		   SRpnt->sense[2], SRpnt->sense[3],
		   SRpnt->sense[4], SRpnt->sense[5],
		   SRpnt->sense[6], SRpnt->sense[7]);
#endif
	}
	else
	    STp->first_frame_position++;
#if DEBUG
	if (debugging) {
	   char sig[8]; int i;
	   for (i=0;i<4;i++)
		   sig[i] = aux->application_sig[i]<32?'^':aux->application_sig[i];
	   sig[4] = '\0';
	   printk(OSST_DEB_MSG 
		"%s:D: AUX: %s UpdFrCt#%d Wpass#%d %s FrSeq#%d LogBlk#%d Qty=%d Sz=%d\n", name, sig,
			ntohl(aux->update_frame_cntr), ntohs(aux->partition.wrt_pass_cntr),
			aux->frame_type==1?"EOD":aux->frame_type==2?"MARK":
			aux->frame_type==8?"HEADR":aux->frame_type==0x80?"DATA":"FILL", 
			ntohl(aux->frame_seq_num), ntohl(aux->logical_blk_num),
			ntohs(aux->dat.dat_list[0].blk_cnt), ntohl(aux->dat.dat_list[0].blk_sz) );
	   if (aux->frame_type==2)
		printk(OSST_DEB_MSG "%s:D: mark_cnt=%d, last_mark_ppos=%d, last_mark_lbn=%d\n", name,
			ntohl(aux->filemark_cnt), ntohl(aux->last_mark_ppos), ntohl(aux->last_mark_lbn));
	   printk(OSST_DEB_MSG "%s:D: Exit read frame from OnStream tape with code %d\n", name, retval);
	}
#endif
	return (retval);
}