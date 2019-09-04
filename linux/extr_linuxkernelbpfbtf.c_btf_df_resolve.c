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
struct resolve_vertex {int /*<<< orphan*/  t; } ;
struct btf_verifier_env {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  btf_verifier_log_basic (struct btf_verifier_env*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int btf_df_resolve(struct btf_verifier_env *env,
			  const struct resolve_vertex *v)
{
	btf_verifier_log_basic(env, v->t, "Unsupported resolve");
	return -EINVAL;
}