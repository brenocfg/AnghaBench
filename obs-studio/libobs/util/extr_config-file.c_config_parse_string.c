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
struct strref {int dummy; } ;
struct lexer {int dummy; } ;
struct TYPE_2__ {char* array; } ;
struct base_token {TYPE_1__ text; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_WHITESPACE ; 
 int /*<<< orphan*/  base_token_clear (struct base_token*) ; 
 scalar_t__ is_newline (char) ; 
 scalar_t__ lexer_getbasetoken (struct lexer*,struct base_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_ref_whitespace (struct strref*) ; 
 int /*<<< orphan*/  strref_add (struct strref*,TYPE_1__*) ; 

__attribute__((used)) static bool config_parse_string(struct lexer *lex, struct strref *ref, char end)
{
	bool success = end != 0;
	struct base_token token;
	base_token_clear(&token);

	while (lexer_getbasetoken(lex, &token, PARSE_WHITESPACE)) {
		if (end) {
			if (*token.text.array == end) {
				success = true;
				break;
			} else if (is_newline(*token.text.array)) {
				success = false;
				break;
			}
		} else {
			if (is_newline(*token.text.array)) {
				success = true;
				break;
			}
		}

		strref_add(ref, &token.text);
	}

	remove_ref_whitespace(ref);
	return success;
}