#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/ * driver_data; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ low_latency; } ;

/* Variables and functions */
 TYPE_1__ sclp_port ; 
 int /*<<< orphan*/  tty_port_tty_set (TYPE_1__*,struct tty_struct*) ; 

__attribute__((used)) static int
sclp_tty_open(struct tty_struct *tty, struct file *filp)
{
	tty_port_tty_set(&sclp_port, tty);
	tty->driver_data = NULL;
	sclp_port.low_latency = 0;
	return 0;
}