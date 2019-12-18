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
struct btf_type {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  btf_type_vlen (struct btf_type const*) ; 
 int /*<<< orphan*/  btf_verifier_log (struct btf_verifier_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btf_struct_log(struct btf_verifier_env *env,
			   const struct btf_type *t)
{
	btf_verifier_log(env, "size=%u vlen=%u", t->size, btf_type_vlen(t));
}