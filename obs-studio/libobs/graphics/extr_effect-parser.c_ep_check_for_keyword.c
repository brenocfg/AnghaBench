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
 int /*<<< orphan*/  LEX_WARNING ; 
 int PARSE_CONTINUE ; 
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int /*<<< orphan*/  cf_adderror (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 int cf_token_is (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline int ep_check_for_keyword(struct effect_parser *ep,
				       const char *keyword, bool *val)
{
	bool new_val = cf_token_is(&ep->cfp, keyword);
	if (new_val) {
		if (!cf_next_valid_token(&ep->cfp))
			return PARSE_EOF;

		if (new_val && *val)
			cf_adderror(&ep->cfp, "'$1' keyword already specified",
				    LEX_WARNING, keyword, NULL, NULL);
		*val = new_val;

		return PARSE_CONTINUE;
	}

	return PARSE_SUCCESS;
}