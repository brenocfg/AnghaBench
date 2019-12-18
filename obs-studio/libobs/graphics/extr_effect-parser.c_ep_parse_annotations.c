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
struct ep_param {int dummy; } ;
struct effect_parser {int /*<<< orphan*/  cfp; } ;
struct darray {int dummy; } ;

/* Variables and functions */
#define  PARSE_BREAK 132 
#define  PARSE_CONTINUE 131 
#define  PARSE_EOF 130 
#define  PARSE_UNEXPECTED_BREAK 129 
#define  PARSE_UNEXPECTED_CONTINUE 128 
 int /*<<< orphan*/  bstrdup (char*) ; 
 int /*<<< orphan*/  cf_adderror_expecting (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cf_adderror_syntax_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  darray_push_back (int,struct darray*,struct ep_param*) ; 
 int /*<<< orphan*/  ep_param_free (struct ep_param*) ; 
 int /*<<< orphan*/  ep_param_init (struct ep_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int ep_parse_param_annotation_var (struct effect_parser*,struct ep_param*) ; 

__attribute__((used)) static int ep_parse_annotations(struct effect_parser *ep,
				struct darray *annotations)
{
	if (!cf_token_is(&ep->cfp, "<")) {
		cf_adderror_expecting(&ep->cfp, "<");
		goto error;
	}

	/* get annotation variables */
	while (true) {
		bool do_break = false;
		struct ep_param var;

		ep_param_init(&var, bstrdup(""), bstrdup(""), false, false,
			      false);

		switch (ep_parse_param_annotation_var(ep, &var)) {
		case PARSE_UNEXPECTED_CONTINUE:
			cf_adderror_syntax_error(&ep->cfp);
			/* Falls through. */
		case PARSE_CONTINUE:
			ep_param_free(&var);
			continue;

		case PARSE_UNEXPECTED_BREAK:
			cf_adderror_syntax_error(&ep->cfp);
			/* Falls through. */
		case PARSE_BREAK:
			ep_param_free(&var);
			do_break = true;
			break;

		case PARSE_EOF:
			ep_param_free(&var);
			goto error;
		}

		if (do_break)
			break;

		darray_push_back(sizeof(struct ep_param), annotations, &var);
	}

	if (!cf_token_is(&ep->cfp, ">")) {
		cf_adderror_expecting(&ep->cfp, ">");
		goto error;
	}
	if (!cf_next_valid_token(&ep->cfp))
		goto error;

	return true;

error:
	return false;
}