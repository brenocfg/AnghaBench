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
struct TYPE_2__ {char* array; } ;
struct base_token {int type; TYPE_1__ text; } ;

/* Variables and functions */
#define  BASETOKEN_ALPHA 132 
#define  BASETOKEN_DIGIT 131 
#define  BASETOKEN_NONE 130 
#define  BASETOKEN_OTHER 129 
#define  BASETOKEN_WHITESPACE 128 
 int /*<<< orphan*/  is_space_or_tab (char) ; 

__attribute__((used)) static bool cf_is_token_break(struct base_token *start_token,
			      const struct base_token *token)
{
	switch (start_token->type) {
	case BASETOKEN_ALPHA:
		if (token->type == BASETOKEN_OTHER ||
		    token->type == BASETOKEN_WHITESPACE)
			return true;
		break;

	case BASETOKEN_DIGIT:
		if (token->type == BASETOKEN_WHITESPACE ||
		    (token->type == BASETOKEN_OTHER &&
		     *token->text.array != '.'))
			return true;
		break;

	case BASETOKEN_WHITESPACE:
		/* lump all non-newline whitespace together when possible */
		if (is_space_or_tab(*start_token->text.array) &&
		    is_space_or_tab(*token->text.array))
			break;
		return true;

	case BASETOKEN_OTHER:
		if (*start_token->text.array == '.' &&
		    token->type == BASETOKEN_DIGIT) {
			start_token->type = BASETOKEN_DIGIT;
			break;
		}
		/* Falls through. */

	case BASETOKEN_NONE:
		return true;
	}

	return false;
}