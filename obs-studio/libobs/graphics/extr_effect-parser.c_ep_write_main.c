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
struct ep_func {char* ret_type; char* mapping; } ;
struct effect_parser {int dummy; } ;
struct dstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  ep_write_main_params (struct effect_parser*,struct dstr*,struct dstr*,struct ep_func*) ; 

__attribute__((used)) static void ep_write_main(struct effect_parser *ep, struct dstr *shader,
			  struct ep_func *func, struct dstr *call_str)
{
	struct dstr param_str;
	struct dstr adjusted_call;

	dstr_init(&param_str);
	dstr_init_copy_dstr(&adjusted_call, call_str);

	dstr_cat(shader, "\n");
	dstr_cat(shader, func->ret_type);
	dstr_cat(shader, " main(");

	ep_write_main_params(ep, shader, &param_str, func);

	dstr_cat(shader, ")");
	if (func->mapping) {
		dstr_cat(shader, " : ");
		dstr_cat(shader, func->mapping);
	}

	dstr_cat(shader, "\n{\n\treturn ");
	dstr_cat_dstr(shader, &adjusted_call);
	dstr_cat(shader, "\n}\n");

	dstr_free(&adjusted_call);
	dstr_free(&param_str);
}