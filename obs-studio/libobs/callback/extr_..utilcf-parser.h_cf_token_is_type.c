#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cf_parser {TYPE_1__* cur_token; } ;
typedef  enum cf_token_type { ____Placeholder_cf_token_type } cf_token_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int PARSE_CONTINUE ; 
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int /*<<< orphan*/  cf_adderror_expecting (struct cf_parser*,char const*) ; 
 int /*<<< orphan*/  cf_go_to_valid_token (struct cf_parser*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int cf_token_is_type(struct cf_parser *p, enum cf_token_type type,
				   const char *type_expected,
				   const char *goto_token)
{
	if (p->cur_token->type != type) {
		cf_adderror_expecting(p, type_expected);
		if (goto_token) {
			if (!cf_go_to_valid_token(p, goto_token, NULL))
				return PARSE_EOF;
		}
		return PARSE_CONTINUE;
	}

	return PARSE_SUCCESS;
}