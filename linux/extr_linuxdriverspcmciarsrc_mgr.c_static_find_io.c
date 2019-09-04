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
struct resource {int dummy; } ;
struct pcmcia_socket {unsigned int io_offset; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int static_find_io(struct pcmcia_socket *s, unsigned int attr,
			unsigned int *base, unsigned int num,
			unsigned int align, struct resource **parent)
{
	if (!s->io_offset)
		return -EINVAL;
	*base = s->io_offset | (*base & 0x0fff);
	*parent = NULL;

	return 0;
}