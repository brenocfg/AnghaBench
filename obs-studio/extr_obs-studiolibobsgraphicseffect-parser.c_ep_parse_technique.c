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
struct ep_technique {int /*<<< orphan*/  passes; int /*<<< orphan*/  name; } ;
struct ep_pass {int /*<<< orphan*/  passes; int /*<<< orphan*/  name; } ;
struct effect_parser {int /*<<< orphan*/  cfp; int /*<<< orphan*/  techniques; } ;

/* Variables and functions */
#define  PARSE_EOF 129 
 scalar_t__ PARSE_SUCCESS ; 
#define  PARSE_UNEXPECTED_CONTINUE 128 
 int /*<<< orphan*/  cf_adderror_expecting (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cf_go_to_token (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ cf_next_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cf_next_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct ep_technique*) ; 
 int ep_parse_pass (struct effect_parser*,struct ep_technique*) ; 
 int /*<<< orphan*/  ep_pass_free (struct ep_technique*) ; 
 int /*<<< orphan*/  ep_pass_init (struct ep_technique*) ; 
 int /*<<< orphan*/  ep_technique_free (struct ep_technique*) ; 
 int /*<<< orphan*/  ep_technique_init (struct ep_technique*) ; 

__attribute__((used)) static void ep_parse_technique(struct effect_parser *ep)
{
	struct ep_technique ept;
	ep_technique_init(&ept);

	if (cf_next_name(&ep->cfp, &ept.name, "name", ";") != PARSE_SUCCESS)
		goto error;

	if (!cf_next_valid_token(&ep->cfp))
		return;

	if (!cf_token_is(&ep->cfp, "{")) {
		if (!cf_go_to_token(&ep->cfp, ";", NULL)) {
			cf_adderror_expecting(&ep->cfp, ";");
			return;
		}

		cf_adderror_expecting(&ep->cfp, "{");
		goto error;
	}
	if (!cf_next_valid_token(&ep->cfp))
		goto error;

	while (!cf_token_is(&ep->cfp, "}")) {
		struct ep_pass pass;
		ep_pass_init(&pass);

		switch (ep_parse_pass(ep, &pass)) {
		case PARSE_UNEXPECTED_CONTINUE:
			ep_pass_free(&pass);
			if (!cf_go_to_token(&ep->cfp, "}", NULL))
				goto error;
			continue;
		case PARSE_EOF:
			ep_pass_free(&pass);
			goto error;
		}

		da_push_back(ept.passes, &pass);

		if (!cf_next_valid_token(&ep->cfp))
			goto error;
	}

	/* pass the current token (which is '}') if we reached here */
	cf_next_token(&ep->cfp);

	da_push_back(ep->techniques, &ept);
	return;

error:
	cf_next_token(&ep->cfp);
	ep_technique_free(&ept);
}