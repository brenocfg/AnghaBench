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
struct TYPE_2__ {int fd; size_t obj_buf_sz; int maps_shndx; int btf_maps_shndx; int data_shndx; int rodata_shndx; int bss_shndx; void* obj_buf; } ;
struct bpf_object {int loaded; int /*<<< orphan*/  list; TYPE_1__ efile; int /*<<< orphan*/  name; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct bpf_object* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  basename (void*) ; 
 int /*<<< orphan*/  bpf_objects_list ; 
 struct bpf_object* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct bpf_object *bpf_object__new(const char *path,
					  void *obj_buf,
					  size_t obj_buf_sz)
{
	struct bpf_object *obj;
	char *end;

	obj = calloc(1, sizeof(struct bpf_object) + strlen(path) + 1);
	if (!obj) {
		pr_warning("alloc memory failed for %s\n", path);
		return ERR_PTR(-ENOMEM);
	}

	strcpy(obj->path, path);
	/* Using basename() GNU version which doesn't modify arg. */
	strncpy(obj->name, basename((void *)path), sizeof(obj->name) - 1);
	end = strchr(obj->name, '.');
	if (end)
		*end = 0;

	obj->efile.fd = -1;
	/*
	 * Caller of this function should also call
	 * bpf_object__elf_finish() after data collection to return
	 * obj_buf to user. If not, we should duplicate the buffer to
	 * avoid user freeing them before elf finish.
	 */
	obj->efile.obj_buf = obj_buf;
	obj->efile.obj_buf_sz = obj_buf_sz;
	obj->efile.maps_shndx = -1;
	obj->efile.btf_maps_shndx = -1;
	obj->efile.data_shndx = -1;
	obj->efile.rodata_shndx = -1;
	obj->efile.bss_shndx = -1;

	obj->loaded = false;

	INIT_LIST_HEAD(&obj->list);
	list_add(&obj->list, &bpf_objects_list);
	return obj;
}