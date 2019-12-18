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
struct TYPE_2__ {int /*<<< orphan*/ * array; } ;
struct cf_token {TYPE_1__ str; } ;
struct base_token {int type; } ;
typedef  enum cf_token_type { ____Placeholder_cf_token_type } cf_token_type ;

/* Variables and functions */
#define  BASETOKEN_ALPHA 132 
#define  BASETOKEN_DIGIT 131 
#define  BASETOKEN_NONE 130 
#define  BASETOKEN_OTHER 129 
#define  BASETOKEN_WHITESPACE 128 
 int CFTOKEN_NAME ; 
 int CFTOKEN_NEWLINE ; 
 int CFTOKEN_NUM ; 
 int CFTOKEN_OTHER ; 
 int CFTOKEN_SPACETAB ; 
 int /*<<< orphan*/  is_newline (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum cf_token_type
cf_get_token_type(const struct cf_token *token,
		  const struct base_token *start_token)
{
	switch (start_token->type) {
	case BASETOKEN_ALPHA:
		return CFTOKEN_NAME;

	case BASETOKEN_DIGIT:
		return CFTOKEN_NUM;

	case BASETOKEN_WHITESPACE:
		if (is_newline(*token->str.array))
			return CFTOKEN_NEWLINE;
		else
			return CFTOKEN_SPACETAB;

	case BASETOKEN_NONE:
	case BASETOKEN_OTHER:
		break;
	}

	return CFTOKEN_OTHER;
}