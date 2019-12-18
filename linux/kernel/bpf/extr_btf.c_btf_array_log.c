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
struct btf_verifier_env {int dummy; } ;
struct btf_type {int dummy; } ;
struct btf_array {int /*<<< orphan*/  nelems; int /*<<< orphan*/  index_type; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct btf_array* btf_type_array (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log (struct btf_verifier_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btf_array_log(struct btf_verifier_env *env,
			  const struct btf_type *t)
{
	const struct btf_array *array = btf_type_array(t);

	btf_verifier_log(env, "type_id=%u index_type_id=%u nr_elems=%u",
			 array->type, array->index_type, array->nelems);
}