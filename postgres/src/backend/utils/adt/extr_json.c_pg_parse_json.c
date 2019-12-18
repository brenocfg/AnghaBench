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
typedef  int JsonTokenType ;
typedef  int /*<<< orphan*/  JsonSemAction ;
typedef  int /*<<< orphan*/  JsonLexContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_PARSE_END ; 
#define  JSON_TOKEN_ARRAY_START 129 
 int /*<<< orphan*/  JSON_TOKEN_END ; 
#define  JSON_TOKEN_OBJECT_START 128 
 int /*<<< orphan*/  json_lex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_expect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lex_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_scalar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pg_parse_json(JsonLexContext *lex, JsonSemAction *sem)
{
	JsonTokenType tok;

	/* get the initial token */
	json_lex(lex);

	tok = lex_peek(lex);

	/* parse by recursive descent */
	switch (tok)
	{
		case JSON_TOKEN_OBJECT_START:
			parse_object(lex, sem);
			break;
		case JSON_TOKEN_ARRAY_START:
			parse_array(lex, sem);
			break;
		default:
			parse_scalar(lex, sem); /* json can be a bare scalar */
	}

	lex_expect(JSON_PARSE_END, lex, JSON_TOKEN_END);

}