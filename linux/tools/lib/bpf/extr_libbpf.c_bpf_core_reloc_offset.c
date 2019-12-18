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
struct ids_vec {int len; int /*<<< orphan*/ * data; } ;
struct hashmap {int dummy; } ;
struct btf_type {int /*<<< orphan*/  name_off; } ;
struct btf {int dummy; } ;
struct bpf_program {int dummy; } ;
struct bpf_offset_reloc {int insn_off; int /*<<< orphan*/  access_str_off; int /*<<< orphan*/  type_id; } ;
struct bpf_core_spec {int offset; TYPE_1__* spec; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  type_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 scalar_t__ IS_ERR (struct ids_vec*) ; 
 int /*<<< orphan*/  LIBBPF_DEBUG ; 
 int PTR_ERR (struct ids_vec*) ; 
 int /*<<< orphan*/  bpf_core_dump_spec (int /*<<< orphan*/ ,struct bpf_core_spec*) ; 
 struct ids_vec* bpf_core_find_cands (struct btf const*,int /*<<< orphan*/ ,struct btf const*) ; 
 int /*<<< orphan*/  bpf_core_free_cands (struct ids_vec*) ; 
 int bpf_core_reloc_insn (struct bpf_program*,int,int,int) ; 
 int bpf_core_spec_match (struct bpf_core_spec*,struct btf const*,int /*<<< orphan*/ ,struct bpf_core_spec*) ; 
 int bpf_core_spec_parse (struct btf const*,int /*<<< orphan*/ ,char const*,struct bpf_core_spec*) ; 
 char* bpf_program__title (struct bpf_program*,int) ; 
 char* btf__name_by_offset (struct btf const*,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (struct btf const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap__find (struct hashmap*,void const*,void**) ; 
 int hashmap__set (struct hashmap*,void const*,struct ids_vec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libbpf_print (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,int,...) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*,int,int,...) ; 
 scalar_t__ str_is_empty (char const*) ; 
 void* u32_as_hash_key (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_core_reloc_offset(struct bpf_program *prog,
				 const struct bpf_offset_reloc *relo,
				 int relo_idx,
				 const struct btf *local_btf,
				 const struct btf *targ_btf,
				 struct hashmap *cand_cache)
{
	const char *prog_name = bpf_program__title(prog, false);
	struct bpf_core_spec local_spec, cand_spec, targ_spec;
	const void *type_key = u32_as_hash_key(relo->type_id);
	const struct btf_type *local_type, *cand_type;
	const char *local_name, *cand_name;
	struct ids_vec *cand_ids;
	__u32 local_id, cand_id;
	const char *spec_str;
	int i, j, err;

	local_id = relo->type_id;
	local_type = btf__type_by_id(local_btf, local_id);
	if (!local_type)
		return -EINVAL;

	local_name = btf__name_by_offset(local_btf, local_type->name_off);
	if (str_is_empty(local_name))
		return -EINVAL;

	spec_str = btf__name_by_offset(local_btf, relo->access_str_off);
	if (str_is_empty(spec_str))
		return -EINVAL;

	err = bpf_core_spec_parse(local_btf, local_id, spec_str, &local_spec);
	if (err) {
		pr_warning("prog '%s': relo #%d: parsing [%d] %s + %s failed: %d\n",
			   prog_name, relo_idx, local_id, local_name, spec_str,
			   err);
		return -EINVAL;
	}

	pr_debug("prog '%s': relo #%d: spec is ", prog_name, relo_idx);
	bpf_core_dump_spec(LIBBPF_DEBUG, &local_spec);
	libbpf_print(LIBBPF_DEBUG, "\n");

	if (!hashmap__find(cand_cache, type_key, (void **)&cand_ids)) {
		cand_ids = bpf_core_find_cands(local_btf, local_id, targ_btf);
		if (IS_ERR(cand_ids)) {
			pr_warning("prog '%s': relo #%d: target candidate search failed for [%d] %s: %ld",
				   prog_name, relo_idx, local_id, local_name,
				   PTR_ERR(cand_ids));
			return PTR_ERR(cand_ids);
		}
		err = hashmap__set(cand_cache, type_key, cand_ids, NULL, NULL);
		if (err) {
			bpf_core_free_cands(cand_ids);
			return err;
		}
	}

	for (i = 0, j = 0; i < cand_ids->len; i++) {
		cand_id = cand_ids->data[i];
		cand_type = btf__type_by_id(targ_btf, cand_id);
		cand_name = btf__name_by_offset(targ_btf, cand_type->name_off);

		err = bpf_core_spec_match(&local_spec, targ_btf,
					  cand_id, &cand_spec);
		pr_debug("prog '%s': relo #%d: matching candidate #%d %s against spec ",
			 prog_name, relo_idx, i, cand_name);
		bpf_core_dump_spec(LIBBPF_DEBUG, &cand_spec);
		libbpf_print(LIBBPF_DEBUG, ": %d\n", err);
		if (err < 0) {
			pr_warning("prog '%s': relo #%d: matching error: %d\n",
				   prog_name, relo_idx, err);
			return err;
		}
		if (err == 0)
			continue;

		if (j == 0) {
			targ_spec = cand_spec;
		} else if (cand_spec.offset != targ_spec.offset) {
			/* if there are many candidates, they should all
			 * resolve to the same offset
			 */
			pr_warning("prog '%s': relo #%d: offset ambiguity: %u != %u\n",
				   prog_name, relo_idx, cand_spec.offset,
				   targ_spec.offset);
			return -EINVAL;
		}

		cand_ids->data[j++] = cand_spec.spec[0].type_id;
	}

	cand_ids->len = j;
	if (cand_ids->len == 0) {
		pr_warning("prog '%s': relo #%d: no matching targets found for [%d] %s + %s\n",
			   prog_name, relo_idx, local_id, local_name, spec_str);
		return -ESRCH;
	}

	err = bpf_core_reloc_insn(prog, relo->insn_off,
				  local_spec.offset, targ_spec.offset);
	if (err) {
		pr_warning("prog '%s': relo #%d: failed to patch insn at offset %d: %d\n",
			   prog_name, relo_idx, relo->insn_off, err);
		return -EINVAL;
	}

	return 0;
}