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
struct comedi_device {scalar_t__ iobase; } ;
struct a2150_board {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct a2150_board const*) ; 
 int ID_BITS (int /*<<< orphan*/ ) ; 
 scalar_t__ STATUS_REG ; 
 struct a2150_board const* a2150_boards ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 

__attribute__((used)) static const struct a2150_board *a2150_probe(struct comedi_device *dev)
{
	int id = ID_BITS(inw(dev->iobase + STATUS_REG));

	if (id >= ARRAY_SIZE(a2150_boards))
		return NULL;

	return &a2150_boards[id];
}