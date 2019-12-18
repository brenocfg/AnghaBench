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
struct cmipci {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static int snd_cmipci_clear_bit_b(struct cmipci *cm, unsigned int cmd, unsigned char flag)
{
	unsigned char val, oval;
	val = oval = inb(cm->iobase + cmd);
	val &= ~flag;
	if (val == oval)
		return 0;
	outb(val, cm->iobase + cmd);
	return 1;
}