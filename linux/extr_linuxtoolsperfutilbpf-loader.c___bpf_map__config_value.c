#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  num; } ;
struct parse_events_term {TYPE_2__ val; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  struct bpf_map_op {scalar_t__ type; int key_size; int value_size; TYPE_1__ v; int /*<<< orphan*/  op_type; } const bpf_map_op ;
struct bpf_map_def {scalar_t__ type; int key_size; int value_size; TYPE_1__ v; int /*<<< orphan*/  op_type; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int BPF_LOADER_ERRNO__INTERNAL ; 
 int BPF_LOADER_ERRNO__OBJCONF_MAP_KEYSIZE ; 
 int BPF_LOADER_ERRNO__OBJCONF_MAP_TYPE ; 
 int BPF_LOADER_ERRNO__OBJCONF_MAP_VALUESIZE ; 
 int /*<<< orphan*/  BPF_MAP_OP_SET_VALUE ; 
 scalar_t__ BPF_MAP_TYPE_ARRAY ; 
 scalar_t__ IS_ERR (struct bpf_map_op const*) ; 
 int PTR_ERR (struct bpf_map_op const*) ; 
 struct bpf_map_op* bpf_map__add_newop (struct bpf_map*,struct parse_events_term*) ; 
 struct bpf_map_op* bpf_map__def (struct bpf_map*) ; 
 char* bpf_map__name (struct bpf_map*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 

__attribute__((used)) static int
__bpf_map__config_value(struct bpf_map *map,
			struct parse_events_term *term)
{
	struct bpf_map_op *op;
	const char *map_name = bpf_map__name(map);
	const struct bpf_map_def *def = bpf_map__def(map);

	if (IS_ERR(def)) {
		pr_debug("Unable to get map definition from '%s'\n",
			 map_name);
		return -BPF_LOADER_ERRNO__INTERNAL;
	}

	if (def->type != BPF_MAP_TYPE_ARRAY) {
		pr_debug("Map %s type is not BPF_MAP_TYPE_ARRAY\n",
			 map_name);
		return -BPF_LOADER_ERRNO__OBJCONF_MAP_TYPE;
	}
	if (def->key_size < sizeof(unsigned int)) {
		pr_debug("Map %s has incorrect key size\n", map_name);
		return -BPF_LOADER_ERRNO__OBJCONF_MAP_KEYSIZE;
	}
	switch (def->value_size) {
	case 1:
	case 2:
	case 4:
	case 8:
		break;
	default:
		pr_debug("Map %s has incorrect value size\n", map_name);
		return -BPF_LOADER_ERRNO__OBJCONF_MAP_VALUESIZE;
	}

	op = bpf_map__add_newop(map, term);
	if (IS_ERR(op))
		return PTR_ERR(op);
	op->op_type = BPF_MAP_OP_SET_VALUE;
	op->v.value = term->val.num;
	return 0;
}