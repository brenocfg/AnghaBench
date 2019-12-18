#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cf_parser {TYPE_2__* cur_token; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;
struct TYPE_4__ {TYPE_1__ str; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFTOKEN_NAME ; 
 int PARSE_SUCCESS ; 
 char* bstrdup_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cf_token_is_type (struct cf_parser*,int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static inline int cf_get_name(struct cf_parser *p, char **dst, const char *name,
			      const char *goto_token)
{
	int errcode;

	errcode = cf_token_is_type(p, CFTOKEN_NAME, name, goto_token);
	if (errcode != PARSE_SUCCESS)
		return errcode;

	*dst = bstrdup_n(p->cur_token->str.array, p->cur_token->str.len);
	return PARSE_SUCCESS;
}