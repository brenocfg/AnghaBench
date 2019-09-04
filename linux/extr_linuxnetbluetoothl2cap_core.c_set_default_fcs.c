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
struct l2cap_chan {scalar_t__ mode; int /*<<< orphan*/  fcs; int /*<<< orphan*/  conf_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_RECV_NO_FCS ; 
 int /*<<< orphan*/  L2CAP_FCS_CRC16 ; 
 int /*<<< orphan*/  L2CAP_FCS_NONE ; 
 scalar_t__ L2CAP_MODE_ERTM ; 
 scalar_t__ L2CAP_MODE_STREAMING ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void set_default_fcs(struct l2cap_chan *chan)
{
	/* FCS is enabled only in ERTM or streaming mode, if one or both
	 * sides request it.
	 */
	if (chan->mode != L2CAP_MODE_ERTM && chan->mode != L2CAP_MODE_STREAMING)
		chan->fcs = L2CAP_FCS_NONE;
	else if (!test_bit(CONF_RECV_NO_FCS, &chan->conf_state))
		chan->fcs = L2CAP_FCS_CRC16;
}