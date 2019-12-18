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
struct ep_var {int /*<<< orphan*/  vars; int /*<<< orphan*/  name; } ;
struct ep_struct {int /*<<< orphan*/  vars; int /*<<< orphan*/  name; } ;
struct effect_parser {int /*<<< orphan*/  structs; int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
#define  PARSE_BREAK 132 
#define  PARSE_CONTINUE 131 
#define  PARSE_EOF 130 
 scalar_t__ PARSE_SUCCESS ; 
#define  PARSE_UNEXPECTED_BREAK 129 
#define  PARSE_UNEXPECTED_CONTINUE 128 
 int /*<<< orphan*/  cf_adderror_syntax_error (int /*<<< orphan*/ *) ; 
 scalar_t__ cf_next_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ cf_next_token_should_be (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct ep_var*) ; 
 int ep_parse_struct_var (struct effect_parser*,struct ep_var*) ; 
 int /*<<< orphan*/  ep_struct_free (struct ep_var*) ; 
 int /*<<< orphan*/  ep_struct_init (struct ep_var*) ; 
 int /*<<< orphan*/  ep_var_free (struct ep_var*) ; 
 int /*<<< orphan*/  ep_var_init (struct ep_var*) ; 

__attribute__((used)) static void ep_parse_struct(struct effect_parser *ep)
{
	struct ep_struct eps;
	ep_struct_init(&eps);

	if (cf_next_name(&ep->cfp, &eps.name, "name", ";") != PARSE_SUCCESS)
		goto error;
	if (cf_next_token_should_be(&ep->cfp, "{", ";", NULL) != PARSE_SUCCESS)
		goto error;

	/* get structure variables */
	while (true) {
		bool do_break = false;
		struct ep_var var;

		ep_var_init(&var);

		switch (ep_parse_struct_var(ep, &var)) {

		case PARSE_UNEXPECTED_CONTINUE:
			cf_adderror_syntax_error(&ep->cfp);
			/* Falls through. */
		case PARSE_CONTINUE:
			ep_var_free(&var);
			continue;

		case PARSE_UNEXPECTED_BREAK:
			cf_adderror_syntax_error(&ep->cfp);
			/* Falls through. */
		case PARSE_BREAK:
			ep_var_free(&var);
			do_break = true;
			break;

		case PARSE_EOF:
			ep_var_free(&var);
			goto error;
		}

		if (do_break)
			break;

		da_push_back(eps.vars, &var);
	}

	if (cf_next_token_should_be(&ep->cfp, ";", NULL, NULL) != PARSE_SUCCESS)
		goto error;

	da_push_back(ep->structs, &eps);
	return;

error:
	ep_struct_free(&eps);
}