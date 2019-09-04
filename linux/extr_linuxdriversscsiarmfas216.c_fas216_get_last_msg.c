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
struct message {int fifo; int* msg; } ;
struct TYPE_5__ {int /*<<< orphan*/  msgs; } ;
struct TYPE_6__ {TYPE_1__ scsi; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */
 int EXTENDED_MESSAGE ; 
 int /*<<< orphan*/  LOG_MESSAGES ; 
 unsigned short NOP ; 
 int /*<<< orphan*/  fas216_log (TYPE_2__*,int /*<<< orphan*/ ,char*,unsigned short,int) ; 
 struct message* msgqueue_getmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned short
fas216_get_last_msg(FAS216_Info *info, int pos)
{
	unsigned short packed_msg = NOP;
	struct message *msg;
	int msgnr = 0;

	while ((msg = msgqueue_getmsg(&info->scsi.msgs, msgnr++)) != NULL) {
		if (pos >= msg->fifo)
			break;
	}

	if (msg) {
		if (msg->msg[0] == EXTENDED_MESSAGE)
			packed_msg = EXTENDED_MESSAGE | msg->msg[2] << 8;
		else
			packed_msg = msg->msg[0];
	}

	fas216_log(info, LOG_MESSAGES,
		"Message: %04x found at position %02x\n", packed_msg, pos);

	return packed_msg;
}