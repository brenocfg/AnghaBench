#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ data_shndx; scalar_t__ rodata_shndx; scalar_t__ bss_shndx; int /*<<< orphan*/  bss; int /*<<< orphan*/  rodata; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  rodata; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  global_data; } ;
struct bpf_object {TYPE_3__ efile; TYPE_2__ sections; TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBBPF_MAP_BSS ; 
 int /*<<< orphan*/  LIBBPF_MAP_DATA ; 
 int /*<<< orphan*/  LIBBPF_MAP_RODATA ; 
 int bpf_object__init_internal_map (struct bpf_object*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bpf_object__init_global_data_maps(struct bpf_object *obj)
{
	int err;

	if (!obj->caps.global_data)
		return 0;
	/*
	 * Populate obj->maps with libbpf internal maps.
	 */
	if (obj->efile.data_shndx >= 0) {
		err = bpf_object__init_internal_map(obj, LIBBPF_MAP_DATA,
						    obj->efile.data_shndx,
						    obj->efile.data,
						    &obj->sections.data);
		if (err)
			return err;
	}
	if (obj->efile.rodata_shndx >= 0) {
		err = bpf_object__init_internal_map(obj, LIBBPF_MAP_RODATA,
						    obj->efile.rodata_shndx,
						    obj->efile.rodata,
						    &obj->sections.rodata);
		if (err)
			return err;
	}
	if (obj->efile.bss_shndx >= 0) {
		err = bpf_object__init_internal_map(obj, LIBBPF_MAP_BSS,
						    obj->efile.bss_shndx,
						    obj->efile.bss, NULL);
		if (err)
			return err;
	}
	return 0;
}