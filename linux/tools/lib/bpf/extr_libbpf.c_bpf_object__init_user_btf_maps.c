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
struct btf_type {int /*<<< orphan*/  name_off; } ;
struct TYPE_2__ {int /*<<< orphan*/  btf_maps_shndx; int /*<<< orphan*/  maps_shndx; int /*<<< orphan*/  elf; } ;
struct bpf_object {TYPE_1__ efile; int /*<<< orphan*/  btf; } ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  MAPS_ELF_SEC ; 
 int bpf_object__init_user_btf_map (struct bpf_object*,struct btf_type const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int btf__get_nr_types (int /*<<< orphan*/ ) ; 
 char* btf__name_by_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btf_is_datasec (struct btf_type const*) ; 
 int btf_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_object__init_user_btf_maps(struct bpf_object *obj, bool strict)
{
	const struct btf_type *sec = NULL;
	int nr_types, i, vlen, err;
	const struct btf_type *t;
	const char *name;
	Elf_Data *data;
	Elf_Scn *scn;

	if (obj->efile.btf_maps_shndx < 0)
		return 0;

	scn = elf_getscn(obj->efile.elf, obj->efile.btf_maps_shndx);
	if (scn)
		data = elf_getdata(scn, NULL);
	if (!scn || !data) {
		pr_warning("failed to get Elf_Data from map section %d (%s)\n",
			   obj->efile.maps_shndx, MAPS_ELF_SEC);
		return -EINVAL;
	}

	nr_types = btf__get_nr_types(obj->btf);
	for (i = 1; i <= nr_types; i++) {
		t = btf__type_by_id(obj->btf, i);
		if (!btf_is_datasec(t))
			continue;
		name = btf__name_by_offset(obj->btf, t->name_off);
		if (strcmp(name, MAPS_ELF_SEC) == 0) {
			sec = t;
			break;
		}
	}

	if (!sec) {
		pr_warning("DATASEC '%s' not found.\n", MAPS_ELF_SEC);
		return -ENOENT;
	}

	vlen = btf_vlen(sec);
	for (i = 0; i < vlen; i++) {
		err = bpf_object__init_user_btf_map(obj, sec, i,
						    obj->efile.btf_maps_shndx,
						    data, strict);
		if (err)
			return err;
	}

	return 0;
}