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
struct TYPE_6__ {char* token_terminator; char* input; int input_length; char* token_start; char* prev_token_terminator; void* token_type; int /*<<< orphan*/  line_number; } ;
typedef  TYPE_1__ JsonLexContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_ALPHANUMERIC_CHAR (char) ; 
 void* JSON_TOKEN_ARRAY_END ; 
 void* JSON_TOKEN_ARRAY_START ; 
 void* JSON_TOKEN_COLON ; 
 void* JSON_TOKEN_COMMA ; 
 void* JSON_TOKEN_END ; 
 void* JSON_TOKEN_FALSE ; 
 void* JSON_TOKEN_NULL ; 
 void* JSON_TOKEN_NUMBER ; 
 void* JSON_TOKEN_OBJECT_END ; 
 void* JSON_TOKEN_OBJECT_START ; 
 void* JSON_TOKEN_STRING ; 
 void* JSON_TOKEN_TRUE ; 
 int /*<<< orphan*/  json_lex_number (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_lex_string (TYPE_1__*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  report_invalid_token (TYPE_1__*) ; 

__attribute__((used)) static inline void
json_lex(JsonLexContext *lex)
{
	char	   *s;
	int			len;

	/* Skip leading whitespace. */
	s = lex->token_terminator;
	len = s - lex->input;
	while (len < lex->input_length &&
		   (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r'))
	{
		if (*s == '\n')
			++lex->line_number;
		++s;
		++len;
	}
	lex->token_start = s;

	/* Determine token type. */
	if (len >= lex->input_length)
	{
		lex->token_start = NULL;
		lex->prev_token_terminator = lex->token_terminator;
		lex->token_terminator = s;
		lex->token_type = JSON_TOKEN_END;
	}
	else
		switch (*s)
		{
				/* Single-character token, some kind of punctuation mark. */
			case '{':
				lex->prev_token_terminator = lex->token_terminator;
				lex->token_terminator = s + 1;
				lex->token_type = JSON_TOKEN_OBJECT_START;
				break;
			case '}':
				lex->prev_token_terminator = lex->token_terminator;
				lex->token_terminator = s + 1;
				lex->token_type = JSON_TOKEN_OBJECT_END;
				break;
			case '[':
				lex->prev_token_terminator = lex->token_terminator;
				lex->token_terminator = s + 1;
				lex->token_type = JSON_TOKEN_ARRAY_START;
				break;
			case ']':
				lex->prev_token_terminator = lex->token_terminator;
				lex->token_terminator = s + 1;
				lex->token_type = JSON_TOKEN_ARRAY_END;
				break;
			case ',':
				lex->prev_token_terminator = lex->token_terminator;
				lex->token_terminator = s + 1;
				lex->token_type = JSON_TOKEN_COMMA;
				break;
			case ':':
				lex->prev_token_terminator = lex->token_terminator;
				lex->token_terminator = s + 1;
				lex->token_type = JSON_TOKEN_COLON;
				break;
			case '"':
				/* string */
				json_lex_string(lex);
				lex->token_type = JSON_TOKEN_STRING;
				break;
			case '-':
				/* Negative number. */
				json_lex_number(lex, s + 1, NULL, NULL);
				lex->token_type = JSON_TOKEN_NUMBER;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				/* Positive number. */
				json_lex_number(lex, s, NULL, NULL);
				lex->token_type = JSON_TOKEN_NUMBER;
				break;
			default:
				{
					char	   *p;

					/*
					 * We're not dealing with a string, number, legal
					 * punctuation mark, or end of string.  The only legal
					 * tokens we might find here are true, false, and null,
					 * but for error reporting purposes we scan until we see a
					 * non-alphanumeric character.  That way, we can report
					 * the whole word as an unexpected token, rather than just
					 * some unintuitive prefix thereof.
					 */
					for (p = s; p - s < lex->input_length - len && JSON_ALPHANUMERIC_CHAR(*p); p++)
						 /* skip */ ;

					/*
					 * We got some sort of unexpected punctuation or an
					 * otherwise unexpected character, so just complain about
					 * that one character.
					 */
					if (p == s)
					{
						lex->prev_token_terminator = lex->token_terminator;
						lex->token_terminator = s + 1;
						report_invalid_token(lex);
					}

					/*
					 * We've got a real alphanumeric token here.  If it
					 * happens to be true, false, or null, all is well.  If
					 * not, error out.
					 */
					lex->prev_token_terminator = lex->token_terminator;
					lex->token_terminator = p;
					if (p - s == 4)
					{
						if (memcmp(s, "true", 4) == 0)
							lex->token_type = JSON_TOKEN_TRUE;
						else if (memcmp(s, "null", 4) == 0)
							lex->token_type = JSON_TOKEN_NULL;
						else
							report_invalid_token(lex);
					}
					else if (p - s == 5 && memcmp(s, "false", 5) == 0)
						lex->token_type = JSON_TOKEN_FALSE;
					else
						report_invalid_token(lex);

				}
		}						/* end of switch */
}