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
struct symbol {int type; scalar_t__ is_declared; int /*<<< orphan*/  name; struct symbol* hash_next; } ;
typedef  enum symbol_type { ____Placeholder_symbol_type } symbol_type ;

/* Variables and functions */
 unsigned long HASH_BUCKETS ; 
 unsigned long crc32 (char const*) ; 
 scalar_t__ map_to_ns (int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct symbol** symtab ; 

struct symbol *find_symbol(const char *name, enum symbol_type ns, int exact)
{
	unsigned long h = crc32(name) % HASH_BUCKETS;
	struct symbol *sym;

	for (sym = symtab[h]; sym; sym = sym->hash_next)
		if (map_to_ns(sym->type) == map_to_ns(ns) &&
		    strcmp(name, sym->name) == 0 &&
		    sym->is_declared)
			break;

	if (exact && sym && sym->type != ns)
		return NULL;
	return sym;
}