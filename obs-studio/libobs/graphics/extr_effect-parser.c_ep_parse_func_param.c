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
struct ep_var {int /*<<< orphan*/  type; int /*<<< orphan*/  mapping; int /*<<< orphan*/  name; int /*<<< orphan*/  var_type; } ;
struct ep_func {int /*<<< orphan*/  sampler_deps; int /*<<< orphan*/  struct_deps; } ;
struct effect_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_VAR_IN ; 
 int /*<<< orphan*/  EP_VAR_INOUT ; 
 int /*<<< orphan*/  EP_VAR_OUT ; 
 int /*<<< orphan*/  EP_VAR_UNIFORM ; 
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int cf_get_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int cf_next_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 scalar_t__ cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ep_check_for_keyword (struct effect_parser*,char*,int*) ; 
 int /*<<< orphan*/ * ep_getsampler (struct effect_parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ep_getstruct (struct effect_parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ep_parse_func_param(struct effect_parser *ep,
				      struct ep_func *func, struct ep_var *var)
{
	int code;
	bool var_type_keyword = false;

	if (!cf_next_valid_token(&ep->cfp))
		return PARSE_EOF;

	code = ep_check_for_keyword(ep, "in", &var_type_keyword);
	if (code == PARSE_EOF)
		return PARSE_EOF;
	else if (var_type_keyword)
		var->var_type = EP_VAR_IN;

	if (!var_type_keyword) {
		code = ep_check_for_keyword(ep, "inout", &var_type_keyword);
		if (code == PARSE_EOF)
			return PARSE_EOF;
		else if (var_type_keyword)
			var->var_type = EP_VAR_INOUT;
	}

	if (!var_type_keyword) {
		code = ep_check_for_keyword(ep, "out", &var_type_keyword);
		if (code == PARSE_EOF)
			return PARSE_EOF;
		else if (var_type_keyword)
			var->var_type = EP_VAR_OUT;
	}

	if (!var_type_keyword) {
		code = ep_check_for_keyword(ep, "uniform", &var_type_keyword);
		if (code == PARSE_EOF)
			return PARSE_EOF;
		else if (var_type_keyword)
			var->var_type = EP_VAR_UNIFORM;
	}

	code = cf_get_name(&ep->cfp, &var->type, "type", ")");
	if (code != PARSE_SUCCESS)
		return code;

	code = cf_next_name(&ep->cfp, &var->name, "name", ")");
	if (code != PARSE_SUCCESS)
		return code;

	if (!cf_next_valid_token(&ep->cfp))
		return PARSE_EOF;

	if (cf_token_is(&ep->cfp, ":")) {
		code = cf_next_name(&ep->cfp, &var->mapping,
				    "mapping specifier", ")");
		if (code != PARSE_SUCCESS)
			return code;

		if (!cf_next_valid_token(&ep->cfp))
			return PARSE_EOF;
	}

	if (ep_getstruct(ep, var->type) != NULL)
		da_push_back(func->struct_deps, &var->type);
	else if (ep_getsampler(ep, var->type) != NULL)
		da_push_back(func->sampler_deps, &var->type);

	return PARSE_SUCCESS;
}