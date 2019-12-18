#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ep_func {int /*<<< orphan*/  contents; } ;
struct TYPE_6__ {TYPE_2__* cur_token; } ;
struct effect_parser {TYPE_3__ cfp; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  str; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NEWLINE ; 
 scalar_t__ CFTOKEN_NONE ; 
 scalar_t__ CFTOKEN_SPACETAB ; 
 scalar_t__ cf_token_is (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dstr_cat_strref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ep_process_func_dep (struct effect_parser*,struct ep_func*) ; 
 scalar_t__ ep_process_param_dep (struct effect_parser*,struct ep_func*) ; 
 scalar_t__ ep_process_sampler_dep (struct effect_parser*,struct ep_func*) ; 
 scalar_t__ ep_process_struct_dep (struct effect_parser*,struct ep_func*) ; 

__attribute__((used)) static inline bool ep_parse_func_contents(struct effect_parser *ep,
					  struct ep_func *func)
{
	int braces = 1;

	dstr_cat_strref(&func->contents, &ep->cfp.cur_token->str);

	while (braces > 0) {
		if ((ep->cfp.cur_token++)->type == CFTOKEN_NONE)
			return false;

		if (ep->cfp.cur_token->type == CFTOKEN_SPACETAB ||
		    ep->cfp.cur_token->type == CFTOKEN_NEWLINE) {
		} else if (cf_token_is(&ep->cfp, "{")) {
			braces++;
		} else if (cf_token_is(&ep->cfp, "}")) {
			braces--;
		} else if (ep_process_struct_dep(ep, func) ||
			   ep_process_func_dep(ep, func) ||
			   ep_process_sampler_dep(ep, func) ||
			   ep_process_param_dep(ep, func)) {
		}

		dstr_cat_strref(&func->contents, &ep->cfp.cur_token->str);
	}

	return true;
}