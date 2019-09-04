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
struct btf_verifier_env {int /*<<< orphan*/  visit_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct btf_verifier_env*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btf_verifier_env_free(struct btf_verifier_env *env)
{
	kvfree(env->visit_states);
	kfree(env);
}