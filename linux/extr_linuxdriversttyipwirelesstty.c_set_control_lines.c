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
struct ipw_tty {int channel_idx; int secondary_channel_idx; int /*<<< orphan*/  hardware; } ;

/* Variables and functions */
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int ipwireless_set_DTR (int /*<<< orphan*/ ,int,int) ; 
 int ipwireless_set_RTS (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int set_control_lines(struct ipw_tty *tty, unsigned int set,
			     unsigned int clear)
{
	int ret;

	if (set & TIOCM_RTS) {
		ret = ipwireless_set_RTS(tty->hardware, tty->channel_idx, 1);
		if (ret)
			return ret;
		if (tty->secondary_channel_idx != -1) {
			ret = ipwireless_set_RTS(tty->hardware,
					  tty->secondary_channel_idx, 1);
			if (ret)
				return ret;
		}
	}
	if (set & TIOCM_DTR) {
		ret = ipwireless_set_DTR(tty->hardware, tty->channel_idx, 1);
		if (ret)
			return ret;
		if (tty->secondary_channel_idx != -1) {
			ret = ipwireless_set_DTR(tty->hardware,
					  tty->secondary_channel_idx, 1);
			if (ret)
				return ret;
		}
	}
	if (clear & TIOCM_RTS) {
		ret = ipwireless_set_RTS(tty->hardware, tty->channel_idx, 0);
		if (tty->secondary_channel_idx != -1) {
			ret = ipwireless_set_RTS(tty->hardware,
					  tty->secondary_channel_idx, 0);
			if (ret)
				return ret;
		}
	}
	if (clear & TIOCM_DTR) {
		ret = ipwireless_set_DTR(tty->hardware, tty->channel_idx, 0);
		if (tty->secondary_channel_idx != -1) {
			ret = ipwireless_set_DTR(tty->hardware,
					  tty->secondary_channel_idx, 0);
			if (ret)
				return ret;
		}
	}
	return 0;
}