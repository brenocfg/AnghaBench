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
struct ref_reloc_sym {int dummy; } ;
struct map {int dummy; } ;
struct kmap {struct ref_reloc_sym* ref_reloc_sym; } ;

/* Variables and functions */
 int /*<<< orphan*/  host_machine ; 
 struct map* machine__kernel_map (int /*<<< orphan*/ ) ; 
 struct kmap* map__kmap (struct map*) ; 
 scalar_t__ map__load (struct map*) ; 

__attribute__((used)) static struct ref_reloc_sym *kernel_get_ref_reloc_sym(void)
{
	/* kmap->ref_reloc_sym should be set if host_machine is initialized */
	struct kmap *kmap;
	struct map *map = machine__kernel_map(host_machine);

	if (map__load(map) < 0)
		return NULL;

	kmap = map__kmap(map);
	if (!kmap)
		return NULL;
	return kmap->ref_reloc_sym;
}