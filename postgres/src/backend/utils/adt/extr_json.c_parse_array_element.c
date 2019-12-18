#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* json_aelem_action ) (int /*<<< orphan*/ ,int) ;
struct TYPE_6__ {int /*<<< orphan*/  semstate; int /*<<< orphan*/  (* array_element_end ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* array_element_start ) (int /*<<< orphan*/ ,int) ;} ;
typedef  int JsonTokenType ;
typedef  TYPE_1__ JsonSemAction ;
typedef  int /*<<< orphan*/  JsonLexContext ;

/* Variables and functions */
#define  JSON_TOKEN_ARRAY_START 129 
 int JSON_TOKEN_NULL ; 
#define  JSON_TOKEN_OBJECT_START 128 
 int lex_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_array (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  parse_scalar (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
parse_array_element(JsonLexContext *lex, JsonSemAction *sem)
{
	json_aelem_action astart = sem->array_element_start;
	json_aelem_action aend = sem->array_element_end;
	JsonTokenType tok = lex_peek(lex);

	bool		isnull;

	isnull = tok == JSON_TOKEN_NULL;

	if (astart != NULL)
		(*astart) (sem->semstate, isnull);

	/* an array element is any object, array or scalar */
	switch (tok)
	{
		case JSON_TOKEN_OBJECT_START:
			parse_object(lex, sem);
			break;
		case JSON_TOKEN_ARRAY_START:
			parse_array(lex, sem);
			break;
		default:
			parse_scalar(lex, sem);
	}

	if (aend != NULL)
		(*aend) (sem->semstate, isnull);
}