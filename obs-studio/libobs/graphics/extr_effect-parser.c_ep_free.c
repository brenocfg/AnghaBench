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
struct effect_parser {TYPE_1__ techniques; TYPE_1__ samplers; TYPE_1__ funcs; TYPE_1__ structs; TYPE_1__ params; int /*<<< orphan*/  cfp; int /*<<< orphan*/ * cur_pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_parser_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  ep_func_free (scalar_t__) ; 
 int /*<<< orphan*/  ep_param_free (scalar_t__) ; 
 int /*<<< orphan*/  ep_sampler_free (scalar_t__) ; 
 int /*<<< orphan*/  ep_struct_free (scalar_t__) ; 
 int /*<<< orphan*/  ep_technique_free (scalar_t__) ; 

void ep_free(struct effect_parser *ep)
{
	size_t i;
	for (i = 0; i < ep->params.num; i++)
		ep_param_free(ep->params.array + i);
	for (i = 0; i < ep->structs.num; i++)
		ep_struct_free(ep->structs.array + i);
	for (i = 0; i < ep->funcs.num; i++)
		ep_func_free(ep->funcs.array + i);
	for (i = 0; i < ep->samplers.num; i++)
		ep_sampler_free(ep->samplers.array + i);
	for (i = 0; i < ep->techniques.num; i++)
		ep_technique_free(ep->techniques.array + i);

	ep->cur_pass = NULL;
	cf_parser_free(&ep->cfp);
	da_free(ep->params);
	da_free(ep->structs);
	da_free(ep->funcs);
	da_free(ep->samplers);
	da_free(ep->techniques);
}