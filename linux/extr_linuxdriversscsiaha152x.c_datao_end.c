#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_8__ {scalar_t__ length; } ;
struct TYPE_6__ {TYPE_3__* buffer; scalar_t__ this_residual; scalar_t__ ptr; int /*<<< orphan*/  buffers_residual; } ;
struct TYPE_7__ {TYPE_1__ SCp; } ;

/* Variables and functions */
 int CH1 ; 
 int CLRCH1 ; 
 int CLRSTCNT ; 
 int /*<<< orphan*/  CMD_INC_RESID (TYPE_2__*,int) ; 
 TYPE_2__* CURRENT_SC ; 
 int DATA_LEN ; 
 int /*<<< orphan*/  DFIFOEMP ; 
 int /*<<< orphan*/  DMACNTRL0 ; 
 int /*<<< orphan*/  DMASTAT ; 
 int GETSTCNT () ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SG_ADDRESS (TYPE_3__*) ; 
 int /*<<< orphan*/  SXFRCTL0 ; 
 scalar_t__ TESTLO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_get_resid (TYPE_2__*) ; 

__attribute__((used)) static void datao_end(struct Scsi_Host *shpnt)
{
	if(TESTLO(DMASTAT, DFIFOEMP)) {
		int data_count = (DATA_LEN - scsi_get_resid(CURRENT_SC)) -
			GETSTCNT();

		CMD_INC_RESID(CURRENT_SC, data_count);

		data_count -= CURRENT_SC->SCp.ptr -
			SG_ADDRESS(CURRENT_SC->SCp.buffer);
		while(data_count>0) {
			CURRENT_SC->SCp.buffer--;
			CURRENT_SC->SCp.buffers_residual++;
			data_count -= CURRENT_SC->SCp.buffer->length;
		}
		CURRENT_SC->SCp.ptr = SG_ADDRESS(CURRENT_SC->SCp.buffer) -
			data_count;
		CURRENT_SC->SCp.this_residual = CURRENT_SC->SCp.buffer->length +
			data_count;
	}

	SETPORT(SXFRCTL0, CH1|CLRCH1|CLRSTCNT);
	SETPORT(SXFRCTL0, CH1);

	SETPORT(DMACNTRL0, 0);
}