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
struct ep_var {char* mapping; char* type; char* name; } ;
struct ep_struct {int dummy; } ;
struct TYPE_2__ {size_t num; struct ep_var* array; } ;
struct ep_func {TYPE_1__ param_vars; } ;
struct effect_parser {int dummy; } ;
struct dstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int dstr_is_empty (struct dstr*) ; 
 struct ep_struct* ep_getstruct (struct effect_parser*,char*) ; 
 int ep_struct_mapped (struct ep_struct*) ; 

__attribute__((used)) static void ep_write_main_params(struct effect_parser *ep, struct dstr *shader,
				 struct dstr *param_str, struct ep_func *func)
{
	size_t i;
	bool empty_params = dstr_is_empty(param_str);

	for (i = 0; i < func->param_vars.num; i++) {
		struct ep_var *var = func->param_vars.array + i;
		struct ep_struct *st = NULL;
		bool mapped = (var->mapping != NULL);

		if (!mapped) {
			st = ep_getstruct(ep, var->type);
			if (st)
				mapped = ep_struct_mapped(st);
		}

		if (mapped) {
			dstr_cat(shader, var->type);
			dstr_cat(shader, " ");
			dstr_cat(shader, var->name);

			if (!st) {
				dstr_cat(shader, " : ");
				dstr_cat(shader, var->mapping);
			}

			if (!dstr_is_empty(param_str))
				dstr_cat(param_str, ", ");
			dstr_cat(param_str, var->name);
		}
	}

	if (!empty_params)
		dstr_cat(param_str, ", ");
}