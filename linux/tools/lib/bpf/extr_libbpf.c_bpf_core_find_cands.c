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
struct ids_vec {int* data; scalar_t__ len; } ;
struct btf_type {int /*<<< orphan*/  name_off; } ;
struct btf {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ids_vec* ERR_PTR (int) ; 
 size_t bpf_core_essential_name_len (char const*) ; 
 int /*<<< orphan*/  bpf_core_free_cands (struct ids_vec*) ; 
 int btf__get_nr_types (struct btf const*) ; 
 char* btf__name_by_offset (struct btf const*,int /*<<< orphan*/ ) ; 
 struct btf_type* btf__type_by_id (struct btf const*,int) ; 
 struct ids_vec* calloc (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char const*,int,char const*) ; 
 int* realloc (int*,scalar_t__) ; 
 scalar_t__ str_is_empty (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static struct ids_vec *bpf_core_find_cands(const struct btf *local_btf,
					   __u32 local_type_id,
					   const struct btf *targ_btf)
{
	size_t local_essent_len, targ_essent_len;
	const char *local_name, *targ_name;
	const struct btf_type *t;
	struct ids_vec *cand_ids;
	__u32 *new_ids;
	int i, err, n;

	t = btf__type_by_id(local_btf, local_type_id);
	if (!t)
		return ERR_PTR(-EINVAL);

	local_name = btf__name_by_offset(local_btf, t->name_off);
	if (str_is_empty(local_name))
		return ERR_PTR(-EINVAL);
	local_essent_len = bpf_core_essential_name_len(local_name);

	cand_ids = calloc(1, sizeof(*cand_ids));
	if (!cand_ids)
		return ERR_PTR(-ENOMEM);

	n = btf__get_nr_types(targ_btf);
	for (i = 1; i <= n; i++) {
		t = btf__type_by_id(targ_btf, i);
		targ_name = btf__name_by_offset(targ_btf, t->name_off);
		if (str_is_empty(targ_name))
			continue;

		targ_essent_len = bpf_core_essential_name_len(targ_name);
		if (targ_essent_len != local_essent_len)
			continue;

		if (strncmp(local_name, targ_name, local_essent_len) == 0) {
			pr_debug("[%d] %s: found candidate [%d] %s\n",
				 local_type_id, local_name, i, targ_name);
			new_ids = realloc(cand_ids->data, cand_ids->len + 1);
			if (!new_ids) {
				err = -ENOMEM;
				goto err_out;
			}
			cand_ids->data = new_ids;
			cand_ids->data[cand_ids->len++] = i;
		}
	}
	return cand_ids;
err_out:
	bpf_core_free_cands(cand_ids);
	return ERR_PTR(err);
}