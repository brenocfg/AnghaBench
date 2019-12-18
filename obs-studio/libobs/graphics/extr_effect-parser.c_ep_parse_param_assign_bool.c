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
struct ep_param {int /*<<< orphan*/  default_val; } ;
struct effect_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int /*<<< orphan*/  cf_adderror_expecting (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 scalar_t__ cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  da_push_back_array (int /*<<< orphan*/ ,long*,int) ; 

__attribute__((used)) static inline int ep_parse_param_assign_bool(struct effect_parser *ep,
					     struct ep_param *param)
{
	if (!cf_next_valid_token(&ep->cfp))
		return PARSE_EOF;

	if (cf_token_is(&ep->cfp, "true")) {
		long l = 1;
		da_push_back_array(param->default_val, &l, sizeof(long));
		return PARSE_SUCCESS;
	} else if (cf_token_is(&ep->cfp, "false")) {
		long l = 0;
		da_push_back_array(param->default_val, &l, sizeof(long));
		return PARSE_SUCCESS;
	}

	cf_adderror_expecting(&ep->cfp, "true or false");

	return PARSE_EOF;
}