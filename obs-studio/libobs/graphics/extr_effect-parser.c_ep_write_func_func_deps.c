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
struct TYPE_2__ {size_t num; char** array; } ;
struct ep_func {int /*<<< orphan*/  written; TYPE_1__ func_deps; } ;
struct effect_parser {int dummy; } ;
struct dstr {int dummy; } ;
struct darray {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 struct ep_func* ep_getfunc (struct effect_parser*,char const*) ; 
 int /*<<< orphan*/  ep_write_func (struct effect_parser*,struct dstr*,struct ep_func*,struct darray*) ; 

__attribute__((used)) static inline void ep_write_func_func_deps(struct effect_parser *ep,
					   struct dstr *shader,
					   struct ep_func *func,
					   struct darray *used_params)
{
	size_t i;
	for (i = 0; i < func->func_deps.num; i++) {
		const char *name = func->func_deps.array[i];
		struct ep_func *func_dep = ep_getfunc(ep, name);

		if (!func_dep->written) {
			ep_write_func(ep, shader, func_dep, used_params);
			dstr_cat(shader, "\n\n");
		}
	}
}