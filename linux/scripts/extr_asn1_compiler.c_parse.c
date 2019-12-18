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
struct type {int flags; struct token* name; TYPE_1__* element; } ;
struct token {scalar_t__ token_type; int line; char* content; } ;
struct TYPE_2__ {struct type* type_def; } ;

/* Variables and functions */
 scalar_t__ TOKEN_ASSIGNMENT ; 
 scalar_t__ TOKEN_TYPE_NAME ; 
 int TYPE_STOP_MARKER ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  exit (int) ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int /*<<< orphan*/  nr_actions ; 
 TYPE_1__* parse_type (struct token**,struct token*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 struct type* type_list ; 
 int /*<<< orphan*/  verbose (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse(void)
{
	struct token *cursor;
	struct type *type;

	/* Parse one type definition statement at a time */
	type = type_list;
	do {
		cursor = type->name;

		if (cursor[0].token_type != TOKEN_TYPE_NAME ||
		    cursor[1].token_type != TOKEN_ASSIGNMENT)
			abort();
		cursor += 2;

		type->element = parse_type(&cursor, type[1].name, NULL);
		type->element->type_def = type;

		if (cursor != type[1].name) {
			fprintf(stderr, "%s:%d: Parse error at token '%s'\n",
				filename, cursor->line, cursor->content);
			exit(1);
		}

	} while (type++, !(type->flags & TYPE_STOP_MARKER));

	verbose("Extracted %u actions\n", nr_actions);
}