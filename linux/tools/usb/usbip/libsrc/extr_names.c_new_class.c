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
struct class {scalar_t__ classid; struct class* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct class** classes ; 
 unsigned int hashnum (scalar_t__) ; 
 struct class* my_malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int new_class(const char *name, u_int8_t classid)
{
	struct class *c;
	unsigned int h = hashnum(classid);

	c = classes[h];
	for (; c; c = c->next)
		if (c->classid == classid)
			return -1;
	c = my_malloc(sizeof(struct class) + strlen(name));
	if (!c)
		return -1;
	strcpy(c->name, name);
	c->classid = classid;
	c->next = classes[h];
	classes[h] = c;
	return 0;
}