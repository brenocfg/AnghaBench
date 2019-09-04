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

/* Variables and functions */
 scalar_t__ EOC ; 
 scalar_t__ PAR_DATA ; 
 scalar_t__ PAR_STATUS ; 
 scalar_t__ RdAddr ; 
 unsigned char inbyte (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline unsigned char read_nibble(short port, unsigned char offset)
{
	unsigned char retval;

	outb(EOC+offset, port + PAR_DATA);
	outb(RdAddr+offset, port + PAR_DATA);
	inbyte(port + PAR_STATUS);	/* Settling time delay */
	retval = inbyte(port + PAR_STATUS);
	outb(EOC+offset, port + PAR_DATA);

	return retval;
}