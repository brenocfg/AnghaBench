#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_6__ {int* firsts; TYPE_1__* device; } ;
typedef  TYPE_2__ scsi_changer ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int lun; } ;

/* Variables and functions */
 size_t CHET_MT ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  DPRINTK (char*,int,int,int) ; 
 int EXCHANGE_MEDIUM ; 
 int ch_do_scsi (TYPE_2__*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ch_exchange(scsi_changer *ch, u_int trans, u_int src,
	    u_int dest1, u_int dest2, int rotate1, int rotate2)
{
	u_char  cmd[12];

	DPRINTK("exchange: 0x%x => 0x%x => 0x%x\n",
		src,dest1,dest2);
	if (0 == trans)
		trans = ch->firsts[CHET_MT];
	memset(cmd,0,sizeof(cmd));
	cmd[0]  = EXCHANGE_MEDIUM;
	cmd[1]  = (ch->device->lun & 0x7) << 5;
	cmd[2]  = (trans >> 8) & 0xff;
	cmd[3]  =  trans       & 0xff;
	cmd[4]  = (src   >> 8) & 0xff;
	cmd[5]  =  src         & 0xff;
	cmd[6]  = (dest1 >> 8) & 0xff;
	cmd[7]  =  dest1       & 0xff;
	cmd[8]  = (dest2 >> 8) & 0xff;
	cmd[9]  =  dest2       & 0xff;
	cmd[10] = (rotate1 ? 1 : 0) | (rotate2 ? 2 : 0);

	return ch_do_scsi(ch, cmd, 12, NULL, 0, DMA_NONE);
}