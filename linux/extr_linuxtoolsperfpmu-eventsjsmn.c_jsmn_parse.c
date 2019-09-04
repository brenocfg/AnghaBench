#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* jsmntype_t ;
struct TYPE_12__ {size_t start; int end; int /*<<< orphan*/  size; void* type; } ;
typedef  TYPE_1__ jsmntok_t ;
typedef  int /*<<< orphan*/  jsmnerr_t ;
struct TYPE_13__ {size_t pos; int toksuper; int toknext; } ;
typedef  TYPE_2__ jsmn_parser ;

/* Variables and functions */
 void* JSMN_ARRAY ; 
 int /*<<< orphan*/  JSMN_ERROR_INVAL ; 
 int /*<<< orphan*/  JSMN_ERROR_NOMEM ; 
 int /*<<< orphan*/  JSMN_ERROR_PART ; 
 void* JSMN_OBJECT ; 
 int /*<<< orphan*/  JSMN_SUCCESS ; 
 TYPE_1__* jsmn_alloc_token (TYPE_2__*,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  jsmn_parse_primitive (TYPE_2__*,char const*,size_t,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  jsmn_parse_string (TYPE_2__*,char const*,size_t,TYPE_1__*,unsigned int) ; 

jsmnerr_t jsmn_parse(jsmn_parser *parser, const char *js, size_t len,
		     jsmntok_t *tokens, unsigned int num_tokens)
{
	jsmnerr_t r;
	int i;
	jsmntok_t *token;

	for (; parser->pos < len; parser->pos++) {
		char c;
		jsmntype_t type;

		c = js[parser->pos];
		switch (c) {
		case '{':
		case '[':
			token = jsmn_alloc_token(parser, tokens, num_tokens);
			if (token == NULL)
				return JSMN_ERROR_NOMEM;
			if (parser->toksuper != -1)
				tokens[parser->toksuper].size++;
			token->type = (c == '{' ? JSMN_OBJECT : JSMN_ARRAY);
			token->start = parser->pos;
			parser->toksuper = parser->toknext - 1;
			break;
		case '}':
		case ']':
			type = (c == '}' ? JSMN_OBJECT : JSMN_ARRAY);
			for (i = parser->toknext - 1; i >= 0; i--) {
				token = &tokens[i];
				if (token->start != -1 && token->end == -1) {
					if (token->type != type)
						return JSMN_ERROR_INVAL;
					parser->toksuper = -1;
					token->end = parser->pos + 1;
					break;
				}
			}
			/* Error if unmatched closing bracket */
			if (i == -1)
				return JSMN_ERROR_INVAL;
			for (; i >= 0; i--) {
				token = &tokens[i];
				if (token->start != -1 && token->end == -1) {
					parser->toksuper = i;
					break;
				}
			}
			break;
		case '\"':
			r = jsmn_parse_string(parser, js, len, tokens,
					      num_tokens);
			if (r < 0)
				return r;
			if (parser->toksuper != -1)
				tokens[parser->toksuper].size++;
			break;
		case '\t':
		case '\r':
		case '\n':
		case ':':
		case ',':
		case ' ':
			break;
#ifdef JSMN_STRICT
			/*
			 * In strict mode primitives are:
			 * numbers and booleans.
			 */
		case '-':
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
		case 't':
		case 'f':
		case 'n':
#else
			/*
			 * In non-strict mode every unquoted value
			 * is a primitive.
			 */
			/*FALL THROUGH */
		default:
#endif
			r = jsmn_parse_primitive(parser, js, len, tokens,
						 num_tokens);
			if (r < 0)
				return r;
			if (parser->toksuper != -1)
				tokens[parser->toksuper].size++;
			break;

#ifdef JSMN_STRICT
			/* Unexpected char in strict mode */
		default:
			return JSMN_ERROR_INVAL;
#endif
		}
	}

	for (i = parser->toknext - 1; i >= 0; i--) {
		/* Unmatched opened object or array */
		if (tokens[i].start != -1 && tokens[i].end == -1)
			return JSMN_ERROR_PART;
	}

	return JSMN_SUCCESS;
}