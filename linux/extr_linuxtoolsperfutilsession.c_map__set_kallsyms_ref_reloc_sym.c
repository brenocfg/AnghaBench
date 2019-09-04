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
typedef  int /*<<< orphan*/  u64 ;
struct ref_reloc_sym {int /*<<< orphan*/  addr; int /*<<< orphan*/ * name; } ;
struct map {int dummy; } ;
struct kmap {struct ref_reloc_sym* ref_reloc_sym; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (struct ref_reloc_sym*) ; 
 struct kmap* map__kmap (struct map*) ; 
 char* strchr (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 struct ref_reloc_sym* zalloc (int) ; 

int map__set_kallsyms_ref_reloc_sym(struct map *map, const char *symbol_name, u64 addr)
{
	char *bracket;
	struct ref_reloc_sym *ref;
	struct kmap *kmap;

	ref = zalloc(sizeof(struct ref_reloc_sym));
	if (ref == NULL)
		return -ENOMEM;

	ref->name = strdup(symbol_name);
	if (ref->name == NULL) {
		free(ref);
		return -ENOMEM;
	}

	bracket = strchr(ref->name, ']');
	if (bracket)
		*bracket = '\0';

	ref->addr = addr;

	kmap = map__kmap(map);
	if (kmap)
		kmap->ref_reloc_sym = ref;

	return 0;
}