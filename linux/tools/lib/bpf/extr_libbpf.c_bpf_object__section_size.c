#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* rodata; TYPE_2__* bss; TYPE_1__* data; } ;
struct bpf_object {TYPE_4__ efile; } ;
typedef  size_t __u32 ;
struct TYPE_7__ {size_t d_size; } ;
struct TYPE_6__ {size_t d_size; } ;
struct TYPE_5__ {size_t d_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int bpf_object_search_section_size (struct bpf_object const*,char const*,size_t*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int bpf_object__section_size(const struct bpf_object *obj, const char *name,
			     __u32 *size)
{
	int ret = -ENOENT;
	size_t d_size;

	*size = 0;
	if (!name) {
		return -EINVAL;
	} else if (!strcmp(name, ".data")) {
		if (obj->efile.data)
			*size = obj->efile.data->d_size;
	} else if (!strcmp(name, ".bss")) {
		if (obj->efile.bss)
			*size = obj->efile.bss->d_size;
	} else if (!strcmp(name, ".rodata")) {
		if (obj->efile.rodata)
			*size = obj->efile.rodata->d_size;
	} else {
		ret = bpf_object_search_section_size(obj, name, &d_size);
		if (!ret)
			*size = d_size;
	}

	return *size ? 0 : ret;
}