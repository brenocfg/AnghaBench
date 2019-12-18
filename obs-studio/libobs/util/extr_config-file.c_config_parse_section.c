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
struct strref {int /*<<< orphan*/  len; int /*<<< orphan*/  array; } ;
struct lexer {int /*<<< orphan*/  offset; } ;
struct config_section {int /*<<< orphan*/  items; } ;
struct config_item {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {char* array; } ;
struct base_token {scalar_t__ type; TYPE_1__ text; } ;

/* Variables and functions */
 scalar_t__ BASETOKEN_OTHER ; 
 scalar_t__ BASETOKEN_WHITESPACE ; 
 int /*<<< orphan*/  PARSE_WHITESPACE ; 
 int /*<<< orphan*/  bstrdup_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzalloc (int) ; 
 int /*<<< orphan*/  config_add_item (int /*<<< orphan*/ *,struct strref*,struct strref*) ; 
 int /*<<< orphan*/  config_parse_string (struct lexer*,struct strref*,char) ; 
 int /*<<< orphan*/  darray_push_back (int,int /*<<< orphan*/ *,struct config_item*) ; 
 int /*<<< orphan*/  is_newline (char) ; 
 scalar_t__ lexer_getbasetoken (struct lexer*,struct base_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strref_clear (struct strref*) ; 
 int /*<<< orphan*/  strref_copy (struct strref*,TYPE_1__*) ; 
 scalar_t__ strref_is_empty (struct strref*) ; 

__attribute__((used)) static void config_parse_section(struct config_section *section,
				 struct lexer *lex)
{
	struct base_token token;

	while (lexer_getbasetoken(lex, &token, PARSE_WHITESPACE)) {
		struct strref name, value;

		while (token.type == BASETOKEN_WHITESPACE) {
			if (!lexer_getbasetoken(lex, &token, PARSE_WHITESPACE))
				return;
		}

		if (token.type == BASETOKEN_OTHER) {
			if (*token.text.array == '#') {
				do {
					if (!lexer_getbasetoken(
						    lex, &token,
						    PARSE_WHITESPACE))
						return;
				} while (!is_newline(*token.text.array));

				continue;
			} else if (*token.text.array == '[') {
				lex->offset--;
				return;
			}
		}

		strref_copy(&name, &token.text);
		if (!config_parse_string(lex, &name, '='))
			continue;

		strref_clear(&value);
		config_parse_string(lex, &value, 0);

		if (strref_is_empty(&value)) {
			struct config_item item;
			item.name = bstrdup_n(name.array, name.len);
			item.value = bzalloc(1);
			darray_push_back(sizeof(struct config_item),
					 &section->items, &item);
		} else {
			config_add_item(&section->items, &name, &value);
		}
	}
}