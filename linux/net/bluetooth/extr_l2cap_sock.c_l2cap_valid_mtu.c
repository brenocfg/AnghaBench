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
typedef  int /*<<< orphan*/  u16 ;
struct l2cap_chan {int scid; } ;

/* Variables and functions */
#define  L2CAP_CID_ATT 128 
 int /*<<< orphan*/  L2CAP_DEFAULT_MIN_MTU ; 
 int /*<<< orphan*/  L2CAP_LE_MIN_MTU ; 

__attribute__((used)) static bool l2cap_valid_mtu(struct l2cap_chan *chan, u16 mtu)
{
	switch (chan->scid) {
	case L2CAP_CID_ATT:
		if (mtu < L2CAP_LE_MIN_MTU)
			return false;
		break;

	default:
		if (mtu < L2CAP_DEFAULT_MIN_MTU)
			return false;
	}

	return true;
}