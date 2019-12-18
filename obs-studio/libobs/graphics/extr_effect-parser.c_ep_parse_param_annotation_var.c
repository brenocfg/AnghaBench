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
struct ep_param {int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct effect_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFTOKEN_NAME ; 
 int PARSE_BREAK ; 
 int PARSE_CONTINUE ; 
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int PARSE_UNEXPECTED_BREAK ; 
 int PARSE_UNEXPECTED_CONTINUE ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_adderror_expecting (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cf_copy_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_go_to_valid_token (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 scalar_t__ cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int cf_token_is_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ep_parse_param_assign (struct effect_parser*,struct ep_param*) ; 

__attribute__((used)) static inline int ep_parse_param_annotation_var(struct effect_parser *ep,
						struct ep_param *var)
{
	int code;

	/* -------------------------------------- */
	/* variable type */

	if (!cf_next_valid_token(&ep->cfp))
		return PARSE_EOF;

	if (cf_token_is(&ep->cfp, ";"))
		return PARSE_CONTINUE;
	if (cf_token_is(&ep->cfp, ">"))
		return PARSE_BREAK;

	code = cf_token_is_type(&ep->cfp, CFTOKEN_NAME, "type name", ";");
	if (code != PARSE_SUCCESS)
		return code;

	bfree(var->type);
	cf_copy_token(&ep->cfp, &var->type);

	/* -------------------------------------- */
	/* variable name */

	if (!cf_next_valid_token(&ep->cfp))
		return PARSE_EOF;

	if (cf_token_is(&ep->cfp, ";")) {
		cf_adderror_expecting(&ep->cfp, "variable name");
		return PARSE_UNEXPECTED_CONTINUE;
	}
	if (cf_token_is(&ep->cfp, ">")) {
		cf_adderror_expecting(&ep->cfp, "variable name");
		return PARSE_UNEXPECTED_BREAK;
	}

	code = cf_token_is_type(&ep->cfp, CFTOKEN_NAME, "variable name", ";");
	if (code != PARSE_SUCCESS)
		return code;

	bfree(var->name);
	cf_copy_token(&ep->cfp, &var->name);

	/* -------------------------------------- */
	/* variable mapping if any (POSITION, TEXCOORD, etc) */

	if (!cf_next_valid_token(&ep->cfp))
		return PARSE_EOF;

	if (cf_token_is(&ep->cfp, ":")) {
		cf_adderror_expecting(&ep->cfp, "= or ;");
		return PARSE_UNEXPECTED_BREAK;
	} else if (cf_token_is(&ep->cfp, ">")) {
		cf_adderror_expecting(&ep->cfp, "= or ;");
		return PARSE_UNEXPECTED_BREAK;
	} else if (cf_token_is(&ep->cfp, "=")) {
		if (!ep_parse_param_assign(ep, var)) {
			cf_adderror_expecting(&ep->cfp, "assignment value");
			return PARSE_UNEXPECTED_BREAK;
		}
	}

	/* -------------------------------------- */

	if (!cf_token_is(&ep->cfp, ";")) {
		if (!cf_go_to_valid_token(&ep->cfp, ";", ">")) {
			cf_adderror_expecting(&ep->cfp, "; or >");
			return PARSE_EOF;
		}
		return PARSE_CONTINUE;
	}

	return PARSE_SUCCESS;
}