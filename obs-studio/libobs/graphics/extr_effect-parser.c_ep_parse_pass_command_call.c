#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct cf_token* cur_token; } ;
struct effect_parser {TYPE_1__ cfp; } ;
struct darray {int dummy; } ;
struct cf_token {int dummy; } ;

/* Variables and functions */
 int PARSE_CONTINUE ; 
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int /*<<< orphan*/  cf_adderror_expecting (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cf_next_valid_token (TYPE_1__*) ; 
 int /*<<< orphan*/  cf_token_clear (struct cf_token*) ; 
 scalar_t__ cf_token_is (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  darray_push_back (int,struct darray*,struct cf_token*) ; 

__attribute__((used)) static inline int ep_parse_pass_command_call(struct effect_parser *ep,
					     struct darray *call)
{
	struct cf_token end_token;
	cf_token_clear(&end_token);

	while (!cf_token_is(&ep->cfp, ";")) {
		if (cf_token_is(&ep->cfp, "}")) {
			cf_adderror_expecting(&ep->cfp, ";");
			return PARSE_CONTINUE;
		}

		darray_push_back(sizeof(struct cf_token), call,
				 ep->cfp.cur_token);
		if (!cf_next_valid_token(&ep->cfp))
			return PARSE_EOF;
	}

	darray_push_back(sizeof(struct cf_token), call, ep->cfp.cur_token);
	darray_push_back(sizeof(struct cf_token), call, &end_token);
	return PARSE_SUCCESS;
}