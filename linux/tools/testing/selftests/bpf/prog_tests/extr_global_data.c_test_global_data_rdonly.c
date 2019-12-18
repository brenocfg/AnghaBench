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
struct bpf_object {int dummy; } ;
struct bpf_map {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  value_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*,char*,int,scalar_t__) ; 
 scalar_t__ CHECK_FAIL (int) ; 
 int ENOMEM ; 
 scalar_t__ EPERM ; 
 TYPE_1__* bpf_map__def (struct bpf_map*) ; 
 int bpf_map__fd (struct bpf_map*) ; 
 int /*<<< orphan*/  bpf_map__is_internal (struct bpf_map*) ; 
 int bpf_map_update_elem (int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bpf_map* bpf_object__find_map_by_name (struct bpf_object*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_global_data_rdonly(struct bpf_object *obj, __u32 duration)
{
	int err = -ENOMEM, map_fd, zero = 0;
	struct bpf_map *map;
	__u8 *buff;

	map = bpf_object__find_map_by_name(obj, "test_glo.rodata");
	if (CHECK_FAIL(!map || !bpf_map__is_internal(map)))
		return;

	map_fd = bpf_map__fd(map);
	if (CHECK_FAIL(map_fd < 0))
		return;

	buff = malloc(bpf_map__def(map)->value_size);
	if (buff)
		err = bpf_map_update_elem(map_fd, &zero, buff, 0);
	free(buff);
	CHECK(!err || errno != EPERM, "test .rodata read-only map",
	      "err %d errno %d\n", err, errno);
}