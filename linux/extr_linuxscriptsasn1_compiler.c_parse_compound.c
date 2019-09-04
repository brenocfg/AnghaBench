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
struct token {scalar_t__ token_type; int line; char* content; } ;
struct element {int flags; struct element* next; } ;

/* Variables and functions */
 int ELEMENT_CONDITIONAL ; 
 int ELEMENT_SKIPPABLE ; 
 scalar_t__ TOKEN_CLOSE_CURLY ; 
 scalar_t__ TOKEN_COMMA ; 
 scalar_t__ TOKEN_ELEMENT_NAME ; 
 scalar_t__ TOKEN_OPEN_CURLY ; 
 int /*<<< orphan*/  exit (int) ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 struct element* parse_type (struct token**,struct token*,struct token*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct element *parse_compound(struct token **_cursor, struct token *end,
				      int alternates)
{
	struct element *children, **child_p = &children, *element;
	struct token *cursor = *_cursor, *name;

	if (cursor->token_type != TOKEN_OPEN_CURLY) {
		fprintf(stderr, "%s:%d: Expected compound to start with brace not '%s'\n",
			filename, cursor->line, cursor->content);
		exit(1);
	}
	cursor++;
	if (cursor >= end)
		goto overrun_error;

	if (cursor->token_type == TOKEN_OPEN_CURLY) {
		fprintf(stderr, "%s:%d: Empty compound\n",
			filename, cursor->line);
		exit(1);
	}

	for (;;) {
		name = NULL;
		if (cursor->token_type == TOKEN_ELEMENT_NAME) {
			name = cursor;
			cursor++;
			if (cursor >= end)
				goto overrun_error;
		}

		element = parse_type(&cursor, end, name);
		if (alternates)
			element->flags |= ELEMENT_SKIPPABLE | ELEMENT_CONDITIONAL;

		*child_p = element;
		child_p = &element->next;

		if (cursor >= end)
			goto overrun_error;
		if (cursor->token_type != TOKEN_COMMA)
			break;
		cursor++;
		if (cursor >= end)
			goto overrun_error;
	}

	children->flags &= ~ELEMENT_CONDITIONAL;

	if (cursor->token_type != TOKEN_CLOSE_CURLY) {
		fprintf(stderr, "%s:%d: Expected compound closure, got '%s'\n",
			filename, cursor->line, cursor->content);
		exit(1);
	}
	cursor++;

	*_cursor = cursor;
	return children;

overrun_error:
	fprintf(stderr, "%s: Unexpectedly hit EOF\n", filename);
	exit(1);
}