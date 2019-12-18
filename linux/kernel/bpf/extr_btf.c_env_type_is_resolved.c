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
typedef  size_t u32 ;
struct btf_verifier_env {scalar_t__* visit_states; } ;

/* Variables and functions */
 scalar_t__ RESOLVED ; 

__attribute__((used)) static bool env_type_is_resolved(const struct btf_verifier_env *env,
				 u32 type_id)
{
	return env->visit_states[type_id] == RESOLVED;
}