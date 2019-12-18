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
struct TYPE_4__ {char* input; int input_length; char* prev_token_terminator; char* token_terminator; } ;
typedef  TYPE_1__ JsonLexContext ;

/* Variables and functions */
 scalar_t__ JSON_ALPHANUMERIC_CHAR (char) ; 
 int /*<<< orphan*/  report_invalid_token (TYPE_1__*) ; 

__attribute__((used)) static inline void
json_lex_number(JsonLexContext *lex, char *s,
				bool *num_err, int *total_len)
{
	bool		error = false;
	int			len = s - lex->input;

	/* Part (1): leading sign indicator. */
	/* Caller already did this for us; so do nothing. */

	/* Part (2): parse main digit string. */
	if (len < lex->input_length && *s == '0')
	{
		s++;
		len++;
	}
	else if (len < lex->input_length && *s >= '1' && *s <= '9')
	{
		do
		{
			s++;
			len++;
		} while (len < lex->input_length && *s >= '0' && *s <= '9');
	}
	else
		error = true;

	/* Part (3): parse optional decimal portion. */
	if (len < lex->input_length && *s == '.')
	{
		s++;
		len++;
		if (len == lex->input_length || *s < '0' || *s > '9')
			error = true;
		else
		{
			do
			{
				s++;
				len++;
			} while (len < lex->input_length && *s >= '0' && *s <= '9');
		}
	}

	/* Part (4): parse optional exponent. */
	if (len < lex->input_length && (*s == 'e' || *s == 'E'))
	{
		s++;
		len++;
		if (len < lex->input_length && (*s == '+' || *s == '-'))
		{
			s++;
			len++;
		}
		if (len == lex->input_length || *s < '0' || *s > '9')
			error = true;
		else
		{
			do
			{
				s++;
				len++;
			} while (len < lex->input_length && *s >= '0' && *s <= '9');
		}
	}

	/*
	 * Check for trailing garbage.  As in json_lex(), any alphanumeric stuff
	 * here should be considered part of the token for error-reporting
	 * purposes.
	 */
	for (; len < lex->input_length && JSON_ALPHANUMERIC_CHAR(*s); s++, len++)
		error = true;

	if (total_len != NULL)
		*total_len = len;

	if (num_err != NULL)
	{
		/* let the caller handle any error */
		*num_err = error;
	}
	else
	{
		/* return token endpoint */
		lex->prev_token_terminator = lex->token_terminator;
		lex->token_terminator = s;
		/* handle error if any */
		if (error)
			report_invalid_token(lex);
	}
}