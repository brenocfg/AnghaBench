#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_5__ {int phase; } ;
struct TYPE_7__ {TYPE_2__* device; TYPE_1__ SCp; } ;
struct TYPE_6__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDMSGO (int /*<<< orphan*/ ) ; 
 TYPE_3__* CURRENT_SC ; 
 int /*<<< orphan*/  IDENTIFY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MESSAGE_REJECT ; 
 scalar_t__ MSGOLEN ; 
 int /*<<< orphan*/  RECONNECT ; 
 int SYNCNEG ; 
 scalar_t__ SYNCRATE ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int syncneg ; 

__attribute__((used)) static void msgo_init(struct Scsi_Host *shpnt)
{
	if(MSGOLEN==0) {
		if((CURRENT_SC->SCp.phase & syncneg) && SYNCNEG==2 && SYNCRATE==0) {
			ADDMSGO(IDENTIFY(RECONNECT, CURRENT_SC->device->lun));
		} else {
			scmd_printk(KERN_INFO, CURRENT_SC,
				    "unexpected MESSAGE OUT phase; rejecting\n");
			ADDMSGO(MESSAGE_REJECT);
		}
	}

}