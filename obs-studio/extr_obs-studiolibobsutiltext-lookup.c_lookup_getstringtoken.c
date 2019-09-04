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
struct strref {char* array; scalar_t__ len; } ;
struct lexer {char* offset; } ;

/* Variables and functions */

__attribute__((used)) static void lookup_getstringtoken(struct lexer *lex, struct strref *token)
{
	const char *temp = lex->offset;
	bool was_backslash  = false;

	while (*temp != 0 && *temp != '\n') {
		if (!was_backslash) {
			if (*temp == '\\') {
				was_backslash = true;
			} else if (*temp == '"') {
				temp++;
				break;
			}
		} else {
			was_backslash = false;
		}

		++temp;
	}

	token->len += (size_t)(temp - lex->offset);

	if (*token->array == '"') {
		token->array++;
		token->len--;

		if (*(temp-1) == '"')
			token->len--;
	}

	lex->offset = temp;
}