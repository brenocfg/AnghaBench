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
typedef  int /*<<< orphan*/  uint32_t ;
struct inbuf {char* ptr; char const* limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  flat_realign (struct inbuf*,int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *flat_read_string(struct inbuf *inb)
{
	int len = 0;
	const char *p = inb->ptr;
	char *str;

	do {
		if (p >= inb->limit)
			die("Premature end of data parsing flat device tree\n");
		len++;
	} while ((*p++) != '\0');

	str = xstrdup(inb->ptr);

	inb->ptr += len;

	flat_realign(inb, sizeof(uint32_t));

	return str;
}