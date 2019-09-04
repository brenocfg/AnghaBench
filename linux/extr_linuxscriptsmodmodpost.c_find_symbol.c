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
struct symbol {int /*<<< orphan*/  name; struct symbol* next; } ;

/* Variables and functions */
 size_t SYMBOL_HASH_SIZE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct symbol** symbolhash ; 
 size_t tdb_hash (char const*) ; 

__attribute__((used)) static struct symbol *find_symbol(const char *name)
{
	struct symbol *s;

	/* For our purposes, .foo matches foo.  PPC64 needs this. */
	if (name[0] == '.')
		name++;

	for (s = symbolhash[tdb_hash(name) % SYMBOL_HASH_SIZE]; s; s = s->next) {
		if (strcmp(s->name, name) == 0)
			return s;
	}
	return NULL;
}