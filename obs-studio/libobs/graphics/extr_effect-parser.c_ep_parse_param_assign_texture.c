#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ep_param {int /*<<< orphan*/  default_val; } ;
struct TYPE_7__ {TYPE_1__* cur_token; } ;
struct effect_parser {TYPE_3__ cfp; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;
struct TYPE_5__ {TYPE_2__ str; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFTOKEN_STRING ; 
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* cf_literal_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_next_valid_token (TYPE_3__*) ; 
 int cf_token_is_type (TYPE_3__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  da_copy_array (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static inline int ep_parse_param_assign_texture(struct effect_parser *ep,
						struct ep_param *param)
{
	int code;
	char *str;

	if (!cf_next_valid_token(&ep->cfp))
		return PARSE_EOF;

	code = cf_token_is_type(&ep->cfp, CFTOKEN_STRING, "texture path string",
				";");
	if (code != PARSE_SUCCESS)
		return code;

	str = cf_literal_to_str(ep->cfp.cur_token->str.array,
				ep->cfp.cur_token->str.len);

	if (str) {
		da_copy_array(param->default_val, str, strlen(str) + 1);
		bfree(str);
	}

	return PARSE_SUCCESS;
}