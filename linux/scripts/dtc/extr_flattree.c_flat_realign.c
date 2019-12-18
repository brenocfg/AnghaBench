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
struct inbuf {int ptr; int base; scalar_t__ limit; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  die (char*) ; 

__attribute__((used)) static void flat_realign(struct inbuf *inb, int align)
{
	int off = inb->ptr - inb->base;

	inb->ptr = inb->base + ALIGN(off, align);
	if (inb->ptr > inb->limit)
		die("Premature end of data parsing flat device tree\n");
}