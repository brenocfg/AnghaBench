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
struct text_lookup {int /*<<< orphan*/  top; } ;
struct text_leaf {int /*<<< orphan*/  lookup; int /*<<< orphan*/  value; } ;
struct strref {char* array; int /*<<< orphan*/  len; } ;
struct lexer {int dummy; } ;

/* Variables and functions */
 struct text_leaf* bmalloc (int) ; 
 int /*<<< orphan*/  bstrdup_n (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_string (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lexer_free (struct lexer*) ; 
 int /*<<< orphan*/  lexer_init (struct lexer*) ; 
 int /*<<< orphan*/  lexer_start (struct lexer*,char const*) ; 
 int /*<<< orphan*/  lookup_addstring (int /*<<< orphan*/ ,struct text_leaf*,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_gettoken (struct lexer*,struct strref*) ; 
 int /*<<< orphan*/  lookup_goto_nextline (struct lexer*) ; 
 int /*<<< orphan*/  strref_clear (struct strref*) ; 

__attribute__((used)) static void lookup_addfiledata(struct text_lookup *lookup,
			       const char *file_data)
{
	struct lexer lex;
	struct strref name, value;

	lexer_init(&lex);
	lexer_start(&lex, file_data);
	strref_clear(&name);
	strref_clear(&value);

	while (lookup_gettoken(&lex, &name)) {
		struct text_leaf *leaf;
		bool got_eq = false;

		if (*name.array == '\n')
			continue;
	getval:
		if (!lookup_gettoken(&lex, &value))
			break;
		if (*value.array == '\n')
			continue;
		else if (!got_eq && *value.array == '=') {
			got_eq = true;
			goto getval;
		}

		leaf = bmalloc(sizeof(struct text_leaf));
		leaf->lookup = bstrdup_n(name.array, name.len);
		leaf->value = convert_string(value.array, value.len);

		lookup_addstring(leaf->lookup, leaf, lookup->top);

		if (!lookup_goto_nextline(&lex))
			break;
	}

	lexer_free(&lex);
}