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
struct btf_verifier_env {int log_type_id; struct btf* btf; } ;
struct btf_type {int dummy; } ;
struct btf_header {int type_off; int type_len; } ;
struct btf {void* nohdr_data; struct btf_header hdr; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  btf_add_type (struct btf_verifier_env*,struct btf_type*) ; 
 scalar_t__ btf_check_meta (struct btf_verifier_env*,struct btf_type*,int) ; 

__attribute__((used)) static int btf_check_all_metas(struct btf_verifier_env *env)
{
	struct btf *btf = env->btf;
	struct btf_header *hdr;
	void *cur, *end;

	hdr = &btf->hdr;
	cur = btf->nohdr_data + hdr->type_off;
	end = cur + hdr->type_len;

	env->log_type_id = 1;
	while (cur < end) {
		struct btf_type *t = cur;
		s32 meta_size;

		meta_size = btf_check_meta(env, t, end - cur);
		if (meta_size < 0)
			return meta_size;

		btf_add_type(env, t);
		cur += meta_size;
		env->log_type_id++;
	}

	return 0;
}