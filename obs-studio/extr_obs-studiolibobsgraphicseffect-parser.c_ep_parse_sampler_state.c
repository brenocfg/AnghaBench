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
struct ep_sampler {int /*<<< orphan*/  name; } ;
struct effect_parser {int /*<<< orphan*/  samplers; int /*<<< orphan*/  cfp; } ;
struct cf_token {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int PARSE_EOF ; 
 scalar_t__ PARSE_SUCCESS ; 
 scalar_t__ cf_next_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ cf_next_token_should_be (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_peek_valid_token (int /*<<< orphan*/ *,struct cf_token*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct ep_sampler*) ; 
 int ep_parse_sampler_state_item (struct effect_parser*,struct ep_sampler*) ; 
 int /*<<< orphan*/  ep_sampler_free (struct ep_sampler*) ; 
 int /*<<< orphan*/  ep_sampler_init (struct ep_sampler*) ; 
 scalar_t__ strref_cmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void ep_parse_sampler_state(struct effect_parser *ep)
{
	struct ep_sampler eps;
	struct cf_token peek;
	ep_sampler_init(&eps);

	if (cf_next_name(&ep->cfp, &eps.name, "name", ";") != PARSE_SUCCESS)
		goto error;
	if (cf_next_token_should_be(&ep->cfp, "{", ";", NULL) != PARSE_SUCCESS)
		goto error;

	if (!cf_peek_valid_token(&ep->cfp, &peek))
		goto error;

	while (strref_cmp(&peek.str, "}") != 0) {
		int ret = ep_parse_sampler_state_item(ep, &eps);
		if (ret == PARSE_EOF)
			goto error;

		if (!cf_peek_valid_token(&ep->cfp, &peek))
			goto error;
	}

	if (cf_next_token_should_be(&ep->cfp, "}", ";", NULL) != PARSE_SUCCESS)
		goto error;
	if (cf_next_token_should_be(&ep->cfp, ";", NULL, NULL) != PARSE_SUCCESS)
		goto error;

	da_push_back(ep->samplers, &eps);
	return;

error:
	ep_sampler_free(&eps);
}