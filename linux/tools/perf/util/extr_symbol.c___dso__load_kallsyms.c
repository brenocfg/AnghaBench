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
struct map {int dummy; } ;
struct kmap {int /*<<< orphan*/  kmaps; } ;
struct dso {scalar_t__ kernel; int /*<<< orphan*/  symtab_type; int /*<<< orphan*/  symbols; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_BINARY_TYPE__GUEST_KALLSYMS ; 
 int /*<<< orphan*/  DSO_BINARY_TYPE__KALLSYMS ; 
 scalar_t__ DSO_TYPE_GUEST_KERNEL ; 
 scalar_t__ dso__load_all_kallsyms (struct dso*,char const*) ; 
 int /*<<< orphan*/  dso__load_kcore (struct dso*,struct map*,char const*) ; 
 scalar_t__ kallsyms__delta (struct kmap*,char const*,int /*<<< orphan*/ *) ; 
 struct kmap* map__kmap (struct map*) ; 
 int map_groups__split_kallsyms (int /*<<< orphan*/ ,struct dso*,int /*<<< orphan*/ ,struct map*) ; 
 int map_groups__split_kallsyms_for_kcore (int /*<<< orphan*/ ,struct dso*) ; 
 scalar_t__ symbol__restricted_filename (char const*,char*) ; 
 int /*<<< orphan*/  symbols__fixup_duplicate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbols__fixup_end (int /*<<< orphan*/ *) ; 

int __dso__load_kallsyms(struct dso *dso, const char *filename,
			 struct map *map, bool no_kcore)
{
	struct kmap *kmap = map__kmap(map);
	u64 delta = 0;

	if (symbol__restricted_filename(filename, "/proc/kallsyms"))
		return -1;

	if (!kmap || !kmap->kmaps)
		return -1;

	if (dso__load_all_kallsyms(dso, filename) < 0)
		return -1;

	if (kallsyms__delta(kmap, filename, &delta))
		return -1;

	symbols__fixup_end(&dso->symbols);
	symbols__fixup_duplicate(&dso->symbols);

	if (dso->kernel == DSO_TYPE_GUEST_KERNEL)
		dso->symtab_type = DSO_BINARY_TYPE__GUEST_KALLSYMS;
	else
		dso->symtab_type = DSO_BINARY_TYPE__KALLSYMS;

	if (!no_kcore && !dso__load_kcore(dso, map, filename))
		return map_groups__split_kallsyms_for_kcore(kmap->kmaps, dso);
	else
		return map_groups__split_kallsyms(kmap->kmaps, dso, delta, map);
}