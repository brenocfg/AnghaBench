#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* json_struct_action ) (int /*<<< orphan*/ ) ;
struct TYPE_11__ {int /*<<< orphan*/  lex_level; } ;
struct TYPE_10__ {int /*<<< orphan*/  semstate; int /*<<< orphan*/  (* array_end ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* array_start ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ JsonSemAction ;
typedef  TYPE_2__ JsonLexContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_PARSE_ARRAY_NEXT ; 
 int /*<<< orphan*/  JSON_PARSE_ARRAY_START ; 
 scalar_t__ JSON_TOKEN_ARRAY_END ; 
 scalar_t__ JSON_TOKEN_ARRAY_START ; 
 int /*<<< orphan*/  JSON_TOKEN_COMMA ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 scalar_t__ lex_accept (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_expect (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 scalar_t__ lex_peek (TYPE_2__*) ; 
 int /*<<< orphan*/  parse_array_element (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_array(JsonLexContext *lex, JsonSemAction *sem)
{
	/*
	 * an array is a possibly empty sequence of array elements, separated by
	 * commas and surrounded by square brackets.
	 */
	json_struct_action astart = sem->array_start;
	json_struct_action aend = sem->array_end;

	check_stack_depth();

	if (astart != NULL)
		(*astart) (sem->semstate);

	/*
	 * Data inside an array is at a higher nesting level than the array
	 * itself. Note that we increment this after we call the semantic routine
	 * for the array start and restore it before we call the routine for the
	 * array end.
	 */
	lex->lex_level++;

	lex_expect(JSON_PARSE_ARRAY_START, lex, JSON_TOKEN_ARRAY_START);
	if (lex_peek(lex) != JSON_TOKEN_ARRAY_END)
	{

		parse_array_element(lex, sem);

		while (lex_accept(lex, JSON_TOKEN_COMMA, NULL))
			parse_array_element(lex, sem);
	}

	lex_expect(JSON_PARSE_ARRAY_NEXT, lex, JSON_TOKEN_ARRAY_END);

	lex->lex_level--;

	if (aend != NULL)
		(*aend) (sem->semstate);
}