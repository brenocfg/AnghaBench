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
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct ep_func {TYPE_1__ sampler_deps; TYPE_1__ param_deps; TYPE_1__ struct_deps; TYPE_1__ func_deps; TYPE_1__ param_vars; int /*<<< orphan*/  contents; int /*<<< orphan*/  mapping; int /*<<< orphan*/  ret_type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ep_var_free (scalar_t__) ; 

__attribute__((used)) static inline void ep_func_free(struct ep_func *epf)
{
	size_t i;
	for (i = 0; i < epf->param_vars.num; i++)
		ep_var_free(epf->param_vars.array + i);

	bfree(epf->name);
	bfree(epf->ret_type);
	bfree(epf->mapping);
	dstr_free(&epf->contents);
	da_free(epf->param_vars);
	da_free(epf->func_deps);
	da_free(epf->struct_deps);
	da_free(epf->param_deps);
	da_free(epf->sampler_deps);
}