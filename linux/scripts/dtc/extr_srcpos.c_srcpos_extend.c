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
struct srcpos {struct srcpos* next; } ;

/* Variables and functions */

struct srcpos *srcpos_extend(struct srcpos *pos, struct srcpos *newtail)
{
	struct srcpos *p;

	if (!pos)
		return newtail;

	for (p = pos; p->next != NULL; p = p->next);
	p->next = newtail;
	return pos;
}