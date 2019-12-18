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
struct inbuf {char* base; char const* limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *flat_read_stringtable(struct inbuf *inb, int offset)
{
	const char *p;

	p = inb->base + offset;
	while (1) {
		if (p >= inb->limit || p < inb->base)
			die("String offset %d overruns string table\n",
			    offset);

		if (*p == '\0')
			break;

		p++;
	}

	return xstrdup(inb->base + offset);
}