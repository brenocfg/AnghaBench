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
struct hashmap {int dummy; } ;
struct btf_type {scalar_t__ name_off; } ;
struct btf_dump_type_aux_state {int name_resolved; } ;
struct btf_dump {char** cached_names; int /*<<< orphan*/  btf; struct btf_dump_type_aux_state* type_states; } ;
typedef  size_t __u32 ;

/* Variables and functions */
 struct btf_type* btf__type_by_id (int /*<<< orphan*/ ,size_t) ; 
 size_t btf_dump_name_dups (struct btf_dump*,struct hashmap*,char const*) ; 
 char* btf_name_of (struct btf_dump*,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,size_t const,char*,char const*,size_t) ; 
 char* strdup (char*) ; 

__attribute__((used)) static const char *btf_dump_resolve_name(struct btf_dump *d, __u32 id,
					 struct hashmap *name_map)
{
	struct btf_dump_type_aux_state *s = &d->type_states[id];
	const struct btf_type *t = btf__type_by_id(d->btf, id);
	const char *orig_name = btf_name_of(d, t->name_off);
	const char **cached_name = &d->cached_names[id];
	size_t dup_cnt;

	if (t->name_off == 0)
		return "";

	if (s->name_resolved)
		return *cached_name ? *cached_name : orig_name;

	dup_cnt = btf_dump_name_dups(d, name_map, orig_name);
	if (dup_cnt > 1) {
		const size_t max_len = 256;
		char new_name[max_len];

		snprintf(new_name, max_len, "%s___%zu", orig_name, dup_cnt);
		*cached_name = strdup(new_name);
	}

	s->name_resolved = 1;
	return *cached_name ? *cached_name : orig_name;
}