#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct map {int dummy; } ;
struct kmap {TYPE_1__* ref_reloc_sym; } ;
struct TYPE_2__ {scalar_t__ addr; scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ kallsyms__get_function_start (char const*,scalar_t__,scalar_t__*) ; 
 struct kmap* map__kmap (struct map*) ; 
 int validate_kcore_modules (char const*,struct map*) ; 

__attribute__((used)) static int validate_kcore_addresses(const char *kallsyms_filename,
				    struct map *map)
{
	struct kmap *kmap = map__kmap(map);

	if (!kmap)
		return -EINVAL;

	if (kmap->ref_reloc_sym && kmap->ref_reloc_sym->name) {
		u64 start;

		if (kallsyms__get_function_start(kallsyms_filename,
						 kmap->ref_reloc_sym->name, &start))
			return -ENOENT;
		if (start != kmap->ref_reloc_sym->addr)
			return -EINVAL;
	}

	return validate_kcore_modules(kallsyms_filename, map);
}