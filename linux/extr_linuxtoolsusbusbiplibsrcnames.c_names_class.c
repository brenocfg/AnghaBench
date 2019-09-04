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
typedef  scalar_t__ u_int8_t ;
struct class {scalar_t__ classid; char const* name; struct class* next; } ;

/* Variables and functions */
 struct class** classes ; 
 size_t hashnum (scalar_t__) ; 

const char *names_class(u_int8_t classid)
{
	struct class *c;

	c = classes[hashnum(classid)];
	for (; c; c = c->next)
		if (c->classid == classid)
			return c->name;
	return NULL;
}