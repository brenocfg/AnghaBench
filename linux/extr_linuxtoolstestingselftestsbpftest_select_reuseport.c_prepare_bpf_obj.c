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
struct bpf_program {int dummy; } ;
struct bpf_object_open_attr {char* file; int /*<<< orphan*/  prog_type; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_SK_REUSEPORT ; 
 int /*<<< orphan*/  CHECK (int,char*,char*,...) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int bpf_map__fd (struct bpf_map*) ; 
 int bpf_map__reuse_fd (struct bpf_map*,int /*<<< orphan*/ ) ; 
 struct bpf_map* bpf_object__find_map_by_name (int /*<<< orphan*/ ,char*) ; 
 int bpf_object__load (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_object__open_xattr (struct bpf_object_open_attr*) ; 
 int bpf_program__fd (struct bpf_program*) ; 
 struct bpf_program* bpf_program__next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_program__set_type (struct bpf_program*,int /*<<< orphan*/ ) ; 
 int data_check_map ; 
 int linum_map ; 
 int /*<<< orphan*/  obj ; 
 int /*<<< orphan*/  outer_map ; 
 int result_map ; 
 int select_by_skb_data_prog ; 
 int tmp_index_ovr_map ; 

__attribute__((used)) static void prepare_bpf_obj(void)
{
	struct bpf_program *prog;
	struct bpf_map *map;
	int err;
	struct bpf_object_open_attr attr = {
		.file = "test_select_reuseport_kern.o",
		.prog_type = BPF_PROG_TYPE_SK_REUSEPORT,
	};

	obj = bpf_object__open_xattr(&attr);
	CHECK(IS_ERR_OR_NULL(obj), "open test_select_reuseport_kern.o",
	      "obj:%p PTR_ERR(obj):%ld\n", obj, PTR_ERR(obj));

	prog = bpf_program__next(NULL, obj);
	CHECK(!prog, "get first bpf_program", "!prog\n");
	bpf_program__set_type(prog, attr.prog_type);

	map = bpf_object__find_map_by_name(obj, "outer_map");
	CHECK(!map, "find outer_map", "!map\n");
	err = bpf_map__reuse_fd(map, outer_map);
	CHECK(err, "reuse outer_map", "err:%d\n", err);

	err = bpf_object__load(obj);
	CHECK(err, "load bpf_object", "err:%d\n", err);

	select_by_skb_data_prog = bpf_program__fd(prog);
	CHECK(select_by_skb_data_prog == -1, "get prog fd",
	      "select_by_skb_data_prog:%d\n", select_by_skb_data_prog);

	map = bpf_object__find_map_by_name(obj, "result_map");
	CHECK(!map, "find result_map", "!map\n");
	result_map = bpf_map__fd(map);
	CHECK(result_map == -1, "get result_map fd",
	      "result_map:%d\n", result_map);

	map = bpf_object__find_map_by_name(obj, "tmp_index_ovr_map");
	CHECK(!map, "find tmp_index_ovr_map", "!map\n");
	tmp_index_ovr_map = bpf_map__fd(map);
	CHECK(tmp_index_ovr_map == -1, "get tmp_index_ovr_map fd",
	      "tmp_index_ovr_map:%d\n", tmp_index_ovr_map);

	map = bpf_object__find_map_by_name(obj, "linum_map");
	CHECK(!map, "find linum_map", "!map\n");
	linum_map = bpf_map__fd(map);
	CHECK(linum_map == -1, "get linum_map fd",
	      "linum_map:%d\n", linum_map);

	map = bpf_object__find_map_by_name(obj, "data_check_map");
	CHECK(!map, "find data_check_map", "!map\n");
	data_check_map = bpf_map__fd(map);
	CHECK(data_check_map == -1, "get data_check_map fd",
	      "data_check_map:%d\n", data_check_map);
}