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
struct subclass {int classid; int subclassid; struct subclass* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int hashnum (int) ; 
 struct subclass* my_malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 struct subclass** subclasses ; 

__attribute__((used)) static int new_subclass(const char *name, u_int8_t classid, u_int8_t subclassid)
{
	struct subclass *s;
	unsigned int h = hashnum((classid << 8) | subclassid);

	s = subclasses[h];
	for (; s; s = s->next)
		if (s->classid == classid && s->subclassid == subclassid)
			return -1;
	s = my_malloc(sizeof(struct subclass) + strlen(name));
	if (!s)
		return -1;
	strcpy(s->name, name);
	s->classid = classid;
	s->subclassid = subclassid;
	s->next = subclasses[h];
	subclasses[h] = s;
	return 0;
}