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
typedef  int u_int8_t ;
struct subclass {int classid; int subclassid; char const* name; struct subclass* next; } ;

/* Variables and functions */
 size_t hashnum (int) ; 
 struct subclass** subclasses ; 

const char *names_subclass(u_int8_t classid, u_int8_t subclassid)
{
	struct subclass *s;

	s = subclasses[hashnum((classid << 8) | subclassid)];
	for (; s; s = s->next)
		if (s->classid == classid && s->subclassid == subclassid)
			return s->name;
	return NULL;
}