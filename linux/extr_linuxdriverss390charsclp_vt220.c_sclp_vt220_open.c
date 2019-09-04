#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ws_row; int ws_col; } ;
struct tty_struct {int count; TYPE_1__ winsize; } ;
struct file {int dummy; } ;
struct TYPE_5__ {scalar_t__ low_latency; } ;

/* Variables and functions */
 TYPE_2__ sclp_vt220_port ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_2__*,struct tty_struct*) ; 

__attribute__((used)) static int
sclp_vt220_open(struct tty_struct *tty, struct file *filp)
{
	if (tty->count == 1) {
		tty_port_tty_set(&sclp_vt220_port, tty);
		sclp_vt220_port.low_latency = 0;
		if (!tty->winsize.ws_row && !tty->winsize.ws_col) {
			tty->winsize.ws_row = 24;
			tty->winsize.ws_col = 80;
		}
	}
	return 0;
}