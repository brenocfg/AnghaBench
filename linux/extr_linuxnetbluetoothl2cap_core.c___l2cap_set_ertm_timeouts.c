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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct l2cap_conf_rfc {void* monitor_timeout; void* retrans_timeout; } ;
struct l2cap_chan {scalar_t__ local_amp_id; TYPE_1__* hs_hcon; } ;
struct TYPE_4__ {int amp_be_flush_to; } ;
struct TYPE_3__ {TYPE_2__* hdev; } ;

/* Variables and functions */
 scalar_t__ AMP_ID_BREDR ; 
 int DIV_ROUND_UP_ULL (int,int) ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_MONITOR_TO ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_RETRANS_TO ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __l2cap_set_ertm_timeouts(struct l2cap_chan *chan,
				      struct l2cap_conf_rfc *rfc)
{
	if (chan->local_amp_id != AMP_ID_BREDR && chan->hs_hcon) {
		u64 ertm_to = chan->hs_hcon->hdev->amp_be_flush_to;

		/* Class 1 devices have must have ERTM timeouts
		 * exceeding the Link Supervision Timeout.  The
		 * default Link Supervision Timeout for AMP
		 * controllers is 10 seconds.
		 *
		 * Class 1 devices use 0xffffffff for their
		 * best-effort flush timeout, so the clamping logic
		 * will result in a timeout that meets the above
		 * requirement.  ERTM timeouts are 16-bit values, so
		 * the maximum timeout is 65.535 seconds.
		 */

		/* Convert timeout to milliseconds and round */
		ertm_to = DIV_ROUND_UP_ULL(ertm_to, 1000);

		/* This is the recommended formula for class 2 devices
		 * that start ERTM timers when packets are sent to the
		 * controller.
		 */
		ertm_to = 3 * ertm_to + 500;

		if (ertm_to > 0xffff)
			ertm_to = 0xffff;

		rfc->retrans_timeout = cpu_to_le16((u16) ertm_to);
		rfc->monitor_timeout = rfc->retrans_timeout;
	} else {
		rfc->retrans_timeout = cpu_to_le16(L2CAP_DEFAULT_RETRANS_TO);
		rfc->monitor_timeout = cpu_to_le16(L2CAP_DEFAULT_MONITOR_TO);
	}
}