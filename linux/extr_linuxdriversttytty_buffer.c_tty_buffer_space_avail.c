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
struct TYPE_2__ {int mem_limit; int /*<<< orphan*/  mem_used; } ;
struct tty_port {TYPE_1__ buf; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int max (int,int /*<<< orphan*/ ) ; 

int tty_buffer_space_avail(struct tty_port *port)
{
	int space = port->buf.mem_limit - atomic_read(&port->buf.mem_used);
	return max(space, 0);
}