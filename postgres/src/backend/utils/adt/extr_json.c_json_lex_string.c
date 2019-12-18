#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int input_length; char* token_start; char* input; char* token_terminator; char* prev_token_terminator; int /*<<< orphan*/ * strval; } ;
typedef  TYPE_1__ JsonLexContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERRCODE_UNTRANSLATABLE_CHARACTER ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetDatabaseEncoding () ; 
 scalar_t__ PG_UTF8 ; 
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  extract_mb_char (char*) ; 
 int pg_mblen (char*) ; 
 int pg_utf_mblen (unsigned char*) ; 
 int /*<<< orphan*/  report_invalid_token (TYPE_1__*) ; 
 int /*<<< orphan*/  report_json_context (TYPE_1__*) ; 
 int /*<<< orphan*/  resetStringInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  unicode_to_utf8 (int,unsigned char*) ; 

__attribute__((used)) static inline void
json_lex_string(JsonLexContext *lex)
{
	char	   *s;
	int			len;
	int			hi_surrogate = -1;

	if (lex->strval != NULL)
		resetStringInfo(lex->strval);

	Assert(lex->input_length > 0);
	s = lex->token_start;
	len = lex->token_start - lex->input;
	for (;;)
	{
		s++;
		len++;
		/* Premature end of the string. */
		if (len >= lex->input_length)
		{
			lex->token_terminator = s;
			report_invalid_token(lex);
		}
		else if (*s == '"')
			break;
		else if ((unsigned char) *s < 32)
		{
			/* Per RFC4627, these characters MUST be escaped. */
			/* Since *s isn't printable, exclude it from the context string */
			lex->token_terminator = s;
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
					 errmsg("invalid input syntax for type %s", "json"),
					 errdetail("Character with value 0x%02x must be escaped.",
							   (unsigned char) *s),
					 report_json_context(lex)));
		}
		else if (*s == '\\')
		{
			/* OK, we have an escape character. */
			s++;
			len++;
			if (len >= lex->input_length)
			{
				lex->token_terminator = s;
				report_invalid_token(lex);
			}
			else if (*s == 'u')
			{
				int			i;
				int			ch = 0;

				for (i = 1; i <= 4; i++)
				{
					s++;
					len++;
					if (len >= lex->input_length)
					{
						lex->token_terminator = s;
						report_invalid_token(lex);
					}
					else if (*s >= '0' && *s <= '9')
						ch = (ch * 16) + (*s - '0');
					else if (*s >= 'a' && *s <= 'f')
						ch = (ch * 16) + (*s - 'a') + 10;
					else if (*s >= 'A' && *s <= 'F')
						ch = (ch * 16) + (*s - 'A') + 10;
					else
					{
						lex->token_terminator = s + pg_mblen(s);
						ereport(ERROR,
								(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
								 errmsg("invalid input syntax for type %s",
										"json"),
								 errdetail("\"\\u\" must be followed by four hexadecimal digits."),
								 report_json_context(lex)));
					}
				}
				if (lex->strval != NULL)
				{
					char		utf8str[5];
					int			utf8len;

					if (ch >= 0xd800 && ch <= 0xdbff)
					{
						if (hi_surrogate != -1)
							ereport(ERROR,
									(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
									 errmsg("invalid input syntax for type %s",
											"json"),
									 errdetail("Unicode high surrogate must not follow a high surrogate."),
									 report_json_context(lex)));
						hi_surrogate = (ch & 0x3ff) << 10;
						continue;
					}
					else if (ch >= 0xdc00 && ch <= 0xdfff)
					{
						if (hi_surrogate == -1)
							ereport(ERROR,
									(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
									 errmsg("invalid input syntax for type %s", "json"),
									 errdetail("Unicode low surrogate must follow a high surrogate."),
									 report_json_context(lex)));
						ch = 0x10000 + hi_surrogate + (ch & 0x3ff);
						hi_surrogate = -1;
					}

					if (hi_surrogate != -1)
						ereport(ERROR,
								(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
								 errmsg("invalid input syntax for type %s", "json"),
								 errdetail("Unicode low surrogate must follow a high surrogate."),
								 report_json_context(lex)));

					/*
					 * For UTF8, replace the escape sequence by the actual
					 * utf8 character in lex->strval. Do this also for other
					 * encodings if the escape designates an ASCII character,
					 * otherwise raise an error.
					 */

					if (ch == 0)
					{
						/* We can't allow this, since our TEXT type doesn't */
						ereport(ERROR,
								(errcode(ERRCODE_UNTRANSLATABLE_CHARACTER),
								 errmsg("unsupported Unicode escape sequence"),
								 errdetail("\\u0000 cannot be converted to text."),
								 report_json_context(lex)));
					}
					else if (GetDatabaseEncoding() == PG_UTF8)
					{
						unicode_to_utf8(ch, (unsigned char *) utf8str);
						utf8len = pg_utf_mblen((unsigned char *) utf8str);
						appendBinaryStringInfo(lex->strval, utf8str, utf8len);
					}
					else if (ch <= 0x007f)
					{
						/*
						 * This is the only way to designate things like a
						 * form feed character in JSON, so it's useful in all
						 * encodings.
						 */
						appendStringInfoChar(lex->strval, (char) ch);
					}
					else
					{
						ereport(ERROR,
								(errcode(ERRCODE_UNTRANSLATABLE_CHARACTER),
								 errmsg("unsupported Unicode escape sequence"),
								 errdetail("Unicode escape values cannot be used for code point values above 007F when the server encoding is not UTF8."),
								 report_json_context(lex)));
					}

				}
			}
			else if (lex->strval != NULL)
			{
				if (hi_surrogate != -1)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
							 errmsg("invalid input syntax for type %s",
									"json"),
							 errdetail("Unicode low surrogate must follow a high surrogate."),
							 report_json_context(lex)));

				switch (*s)
				{
					case '"':
					case '\\':
					case '/':
						appendStringInfoChar(lex->strval, *s);
						break;
					case 'b':
						appendStringInfoChar(lex->strval, '\b');
						break;
					case 'f':
						appendStringInfoChar(lex->strval, '\f');
						break;
					case 'n':
						appendStringInfoChar(lex->strval, '\n');
						break;
					case 'r':
						appendStringInfoChar(lex->strval, '\r');
						break;
					case 't':
						appendStringInfoChar(lex->strval, '\t');
						break;
					default:
						/* Not a valid string escape, so error out. */
						lex->token_terminator = s + pg_mblen(s);
						ereport(ERROR,
								(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
								 errmsg("invalid input syntax for type %s",
										"json"),
								 errdetail("Escape sequence \"\\%s\" is invalid.",
										   extract_mb_char(s)),
								 report_json_context(lex)));
				}
			}
			else if (strchr("\"\\/bfnrt", *s) == NULL)
			{
				/*
				 * Simpler processing if we're not bothered about de-escaping
				 *
				 * It's very tempting to remove the strchr() call here and
				 * replace it with a switch statement, but testing so far has
				 * shown it's not a performance win.
				 */
				lex->token_terminator = s + pg_mblen(s);
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type %s", "json"),
						 errdetail("Escape sequence \"\\%s\" is invalid.",
								   extract_mb_char(s)),
						 report_json_context(lex)));
			}

		}
		else if (lex->strval != NULL)
		{
			if (hi_surrogate != -1)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("invalid input syntax for type %s", "json"),
						 errdetail("Unicode low surrogate must follow a high surrogate."),
						 report_json_context(lex)));

			appendStringInfoChar(lex->strval, *s);
		}

	}

	if (hi_surrogate != -1)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s", "json"),
				 errdetail("Unicode low surrogate must follow a high surrogate."),
				 report_json_context(lex)));

	/* Hooray, we found the end of the string! */
	lex->prev_token_terminator = lex->token_terminator;
	lex->token_terminator = s + 1;
}