#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* input; char* token_terminator; char* line_start; int line_number; int input_length; int /*<<< orphan*/  strval; } ;
typedef  TYPE_1__ JsonLexContext ;

/* Variables and functions */
 int /*<<< orphan*/  makeStringInfo () ; 
 TYPE_1__* palloc0 (int) ; 

JsonLexContext *
makeJsonLexContextCstringLen(char *json, int len, bool need_escapes)
{
	JsonLexContext *lex = palloc0(sizeof(JsonLexContext));

	lex->input = lex->token_terminator = lex->line_start = json;
	lex->line_number = 1;
	lex->input_length = len;
	if (need_escapes)
		lex->strval = makeStringInfo();
	return lex;
}