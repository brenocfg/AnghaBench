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
typedef  int u8 ;
struct l2cap_chan {scalar_t__ chan_type; scalar_t__ sec_level; } ;

/* Variables and functions */
 scalar_t__ BT_SECURITY_FIPS ; 
 scalar_t__ BT_SECURITY_HIGH ; 
 scalar_t__ BT_SECURITY_MEDIUM ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 scalar_t__ L2CAP_CHAN_CONN_ORIENTED ; 
 int /*<<< orphan*/  L2CAP_ENC_TIMEOUT ; 
 int /*<<< orphan*/  __clear_chan_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __set_chan_timer (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_close (struct l2cap_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void l2cap_check_encryption(struct l2cap_chan *chan, u8 encrypt)
{
	if (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED)
		return;

	if (encrypt == 0x00) {
		if (chan->sec_level == BT_SECURITY_MEDIUM) {
			__set_chan_timer(chan, L2CAP_ENC_TIMEOUT);
		} else if (chan->sec_level == BT_SECURITY_HIGH ||
			   chan->sec_level == BT_SECURITY_FIPS)
			l2cap_chan_close(chan, ECONNREFUSED);
	} else {
		if (chan->sec_level == BT_SECURITY_MEDIUM)
			__clear_chan_timer(chan);
	}
}