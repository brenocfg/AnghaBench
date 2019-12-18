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
struct btf_ext {int dummy; } ;
struct btf_dedup_opts {int dummy; } ;
struct btf_dedup {int dummy; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct btf_dedup*) ; 
 int PTR_ERR (struct btf_dedup*) ; 
 int btf_dedup_compact_types (struct btf_dedup*) ; 
 int /*<<< orphan*/  btf_dedup_free (struct btf_dedup*) ; 
 struct btf_dedup* btf_dedup_new (struct btf*,struct btf_ext*,struct btf_dedup_opts const*) ; 
 int btf_dedup_prim_types (struct btf_dedup*) ; 
 int btf_dedup_ref_types (struct btf_dedup*) ; 
 int btf_dedup_remap_types (struct btf_dedup*) ; 
 int btf_dedup_strings (struct btf_dedup*) ; 
 int btf_dedup_struct_types (struct btf_dedup*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

int btf__dedup(struct btf *btf, struct btf_ext *btf_ext,
	       const struct btf_dedup_opts *opts)
{
	struct btf_dedup *d = btf_dedup_new(btf, btf_ext, opts);
	int err;

	if (IS_ERR(d)) {
		pr_debug("btf_dedup_new failed: %ld", PTR_ERR(d));
		return -EINVAL;
	}

	err = btf_dedup_strings(d);
	if (err < 0) {
		pr_debug("btf_dedup_strings failed:%d\n", err);
		goto done;
	}
	err = btf_dedup_prim_types(d);
	if (err < 0) {
		pr_debug("btf_dedup_prim_types failed:%d\n", err);
		goto done;
	}
	err = btf_dedup_struct_types(d);
	if (err < 0) {
		pr_debug("btf_dedup_struct_types failed:%d\n", err);
		goto done;
	}
	err = btf_dedup_ref_types(d);
	if (err < 0) {
		pr_debug("btf_dedup_ref_types failed:%d\n", err);
		goto done;
	}
	err = btf_dedup_compact_types(d);
	if (err < 0) {
		pr_debug("btf_dedup_compact_types failed:%d\n", err);
		goto done;
	}
	err = btf_dedup_remap_types(d);
	if (err < 0) {
		pr_debug("btf_dedup_remap_types failed:%d\n", err);
		goto done;
	}

done:
	btf_dedup_free(d);
	return err;
}