#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* array; scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct cf_token {int /*<<< orphan*/  type; TYPE_3__ unmerged_str; TYPE_1__ str; } ;
struct TYPE_5__ {char* offset; } ;
struct cf_lexer {TYPE_2__ base_lexer; scalar_t__* write_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFTOKEN_STRING ; 
 int /*<<< orphan*/  cf_lexer_write_strref (struct cf_lexer*,TYPE_3__*) ; 
 int /*<<< orphan*/  cf_pass_any_splices (char const**) ; 
 scalar_t__ is_newline (char const) ; 

__attribute__((used)) static void cf_lexer_getstrtoken(struct cf_lexer *lex,
				 struct cf_token *out_token, char delimiter,
				 bool allow_escaped_delimiters)
{
	const char *offset = lex->base_lexer.offset;
	bool escaped = false;

	out_token->unmerged_str.len++;
	out_token->str.len++;
	cf_lexer_write_strref(lex, &out_token->unmerged_str);

	while (*offset) {
		cf_pass_any_splices(&offset);
		if (*offset == delimiter) {
			if (!escaped) {
				*lex->write_offset++ = *offset;
				out_token->str.len++;
				offset++;
				break;
			}
		} else if (is_newline(*offset)) {
			break;
		}

		*lex->write_offset++ = *offset;
		out_token->str.len++;

		escaped = (allow_escaped_delimiters && *offset == '\\');
		offset++;
	}

	*lex->write_offset = 0;
	out_token->unmerged_str.len +=
		(size_t)(offset - out_token->unmerged_str.array);
	out_token->type = CFTOKEN_STRING;
	lex->base_lexer.offset = offset;
}