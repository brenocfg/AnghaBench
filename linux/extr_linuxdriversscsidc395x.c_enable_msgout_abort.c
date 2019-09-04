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
struct ScsiReqBlk {int msg_count; int /*<<< orphan*/  state; int /*<<< orphan*/ * msgout_buf; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  DC395x_ENABLE_MSGOUT ; 
 int /*<<< orphan*/  SRB_MSGIN ; 
 int /*<<< orphan*/  SRB_MSGOUT ; 

__attribute__((used)) static inline void enable_msgout_abort(struct AdapterCtlBlk *acb,
		struct ScsiReqBlk *srb)
{
	srb->msgout_buf[0] = ABORT;
	srb->msg_count = 1;
	DC395x_ENABLE_MSGOUT;
	srb->state &= ~SRB_MSGIN;
	srb->state |= SRB_MSGOUT;
}