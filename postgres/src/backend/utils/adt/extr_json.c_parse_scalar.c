#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* json_scalar_action ) (int /*<<< orphan*/ ,char*,int) ;
struct TYPE_3__ {int /*<<< orphan*/  semstate; int /*<<< orphan*/  (* scalar ) (int /*<<< orphan*/ ,char*,int) ;} ;
typedef  int JsonTokenType ;
typedef  TYPE_1__ JsonSemAction ;
typedef  int /*<<< orphan*/  JsonLexContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_PARSE_VALUE ; 
#define  JSON_TOKEN_FALSE 132 
#define  JSON_TOKEN_NULL 131 
#define  JSON_TOKEN_NUMBER 130 
#define  JSON_TOKEN_STRING 129 
#define  JSON_TOKEN_TRUE 128 
 int /*<<< orphan*/  lex_accept (int /*<<< orphan*/ *,int const,char**) ; 
 int lex_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_parse_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline void
parse_scalar(JsonLexContext *lex, JsonSemAction *sem)
{
	char	   *val = NULL;
	json_scalar_action sfunc = sem->scalar;
	char	  **valaddr;
	JsonTokenType tok = lex_peek(lex);

	valaddr = sfunc == NULL ? NULL : &val;

	/* a scalar must be a string, a number, true, false, or null */
	switch (tok)
	{
		case JSON_TOKEN_TRUE:
			lex_accept(lex, JSON_TOKEN_TRUE, valaddr);
			break;
		case JSON_TOKEN_FALSE:
			lex_accept(lex, JSON_TOKEN_FALSE, valaddr);
			break;
		case JSON_TOKEN_NULL:
			lex_accept(lex, JSON_TOKEN_NULL, valaddr);
			break;
		case JSON_TOKEN_NUMBER:
			lex_accept(lex, JSON_TOKEN_NUMBER, valaddr);
			break;
		case JSON_TOKEN_STRING:
			lex_accept(lex, JSON_TOKEN_STRING, valaddr);
			break;
		default:
			report_parse_error(JSON_PARSE_VALUE, lex);
	}

	if (sfunc != NULL)
		(*sfunc) (sem->semstate, val, tok);
}