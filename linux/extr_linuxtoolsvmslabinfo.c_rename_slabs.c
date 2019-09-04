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
struct slabinfo {char* name; int refs; } ;
struct aliasinfo {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  actual_slabs ; 
 struct aliasinfo* find_one_alias (struct slabinfo*) ; 
 int /*<<< orphan*/  show_first_alias ; 
 struct slabinfo* slabinfo ; 
 int slabs ; 

__attribute__((used)) static void rename_slabs(void)
{
	struct slabinfo *s;
	struct aliasinfo *a;

	for (s = slabinfo; s < slabinfo + slabs; s++) {
		if (*s->name != ':')
			continue;

		if (s->refs > 1 && !show_first_alias)
			continue;

		a = find_one_alias(s);

		if (a)
			s->name = a->name;
		else {
			s->name = "*";
			actual_slabs--;
		}
	}
}