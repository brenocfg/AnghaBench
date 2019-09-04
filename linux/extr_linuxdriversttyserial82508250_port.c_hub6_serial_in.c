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
struct uart_port {int regshift; int hub6; scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static unsigned int hub6_serial_in(struct uart_port *p, int offset)
{
	offset = offset << p->regshift;
	outb(p->hub6 - 1 + offset, p->iobase);
	return inb(p->iobase + 1);
}