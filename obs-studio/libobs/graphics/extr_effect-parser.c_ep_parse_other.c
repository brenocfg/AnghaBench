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
struct effect_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 scalar_t__ PARSE_SUCCESS ; 
 int /*<<< orphan*/  bfree (char*) ; 
 scalar_t__ cf_get_name (int /*<<< orphan*/ *,char**,char*,char*) ; 
 scalar_t__ cf_next_name (int /*<<< orphan*/ *,char**,char*,char*) ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 scalar_t__ cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ep_get_var_specifiers (struct effect_parser*,int*,int*,int*) ; 
 int /*<<< orphan*/  ep_parse_function (struct effect_parser*,char*,char*) ; 
 int /*<<< orphan*/  ep_parse_param (struct effect_parser*,char*,char*,int,int,int) ; 
 int /*<<< orphan*/  report_invalid_func_keyword (struct effect_parser*,char*,int) ; 

__attribute__((used)) static void ep_parse_other(struct effect_parser *ep)
{
	bool is_property = false, is_const = false, is_uniform = false;
	char *type = NULL, *name = NULL;

	if (!ep_get_var_specifiers(ep, &is_property, &is_const, &is_uniform))
		goto error;

	if (cf_get_name(&ep->cfp, &type, "type", ";") != PARSE_SUCCESS)
		goto error;
	if (cf_next_name(&ep->cfp, &name, "name", ";") != PARSE_SUCCESS)
		goto error;
	if (!cf_next_valid_token(&ep->cfp))
		goto error;

	if (cf_token_is(&ep->cfp, "(")) {
		report_invalid_func_keyword(ep, "property", is_property);
		report_invalid_func_keyword(ep, "const", is_const);
		report_invalid_func_keyword(ep, "uniform", is_uniform);

		ep_parse_function(ep, type, name);
		return;
	} else {
		ep_parse_param(ep, type, name, is_property, is_const,
			       is_uniform);
		return;
	}

error:
	bfree(type);
	bfree(name);
}