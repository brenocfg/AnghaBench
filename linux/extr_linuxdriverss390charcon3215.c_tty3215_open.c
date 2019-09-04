#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct raw3215_info* driver_data; } ;
struct TYPE_2__ {scalar_t__ low_latency; } ;
struct raw3215_info {TYPE_1__ port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int raw3215_startup (struct raw3215_info*) ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_1__*,struct tty_struct*) ; 

__attribute__((used)) static int tty3215_open(struct tty_struct *tty, struct file * filp)
{
	struct raw3215_info *raw = tty->driver_data;
	int retval;

	tty_port_tty_set(&raw->port, tty);

	raw->port.low_latency = 0; /* don't use bottom half for pushing chars */
	/*
	 * Start up 3215 device
	 */
	retval = raw3215_startup(raw);
	if (retval)
		return retval;

	return 0;
}