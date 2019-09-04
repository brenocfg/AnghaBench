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
struct inbuf {scalar_t__ ptr; scalar_t__ limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 

__attribute__((used)) static void flat_read_chunk(struct inbuf *inb, void *p, int len)
{
	if ((inb->ptr + len) > inb->limit)
		die("Premature end of data parsing flat device tree\n");

	memcpy(p, inb->ptr, len);

	inb->ptr += len;
}