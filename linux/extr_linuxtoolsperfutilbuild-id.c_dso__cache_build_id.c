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
struct machine {char* mmap_name; } ;
struct dso {char* long_name; int /*<<< orphan*/  nsinfo; int /*<<< orphan*/  build_id; } ;

/* Variables and functions */
 int build_id_cache__add_b (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int,int) ; 
 int dso__is_kallsyms (struct dso*) ; 
 scalar_t__ dso__is_kcore (struct dso*) ; 
 int dso__is_vdso (struct dso*) ; 

__attribute__((used)) static int dso__cache_build_id(struct dso *dso, struct machine *machine)
{
	bool is_kallsyms = dso__is_kallsyms(dso);
	bool is_vdso = dso__is_vdso(dso);
	const char *name = dso->long_name;

	if (dso__is_kcore(dso)) {
		is_kallsyms = true;
		name = machine->mmap_name;
	}
	return build_id_cache__add_b(dso->build_id, sizeof(dso->build_id), name,
				     dso->nsinfo, is_kallsyms, is_vdso);
}