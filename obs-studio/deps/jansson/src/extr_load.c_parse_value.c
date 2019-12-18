#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* val; size_t len; } ;
struct TYPE_9__ {int /*<<< orphan*/  real; int /*<<< orphan*/  integer; TYPE_1__ string; } ;
struct TYPE_10__ {scalar_t__ depth; int token; TYPE_2__ value; } ;
typedef  TYPE_3__ lex_t ;
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 size_t JSON_ALLOW_NUL ; 
 scalar_t__ JSON_PARSER_MAX_DEPTH ; 
#define  TOKEN_FALSE 134 
#define  TOKEN_INTEGER 133 
#define  TOKEN_INVALID 132 
#define  TOKEN_NULL 131 
#define  TOKEN_REAL 130 
#define  TOKEN_STRING 129 
#define  TOKEN_TRUE 128 
 int /*<<< orphan*/  error_set (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * json_false () ; 
 int /*<<< orphan*/ * json_integer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_null () ; 
 int /*<<< orphan*/ * json_real (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_true () ; 
 int /*<<< orphan*/ * jsonp_stringn_nocheck_own (char const*,size_t) ; 
 int /*<<< orphan*/  memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/ * parse_array (TYPE_3__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_object (TYPE_3__*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static json_t *parse_value(lex_t *lex, size_t flags, json_error_t *error)
{
    json_t *json;

    lex->depth++;
    if(lex->depth > JSON_PARSER_MAX_DEPTH) {
        error_set(error, lex, "maximum parsing depth reached");
        return NULL;
    }

    switch(lex->token) {
        case TOKEN_STRING: {
            const char *value = lex->value.string.val;
            size_t len = lex->value.string.len;

            if(!(flags & JSON_ALLOW_NUL)) {
                if(memchr(value, '\0', len)) {
                    error_set(error, lex, "\\u0000 is not allowed without JSON_ALLOW_NUL");
                    return NULL;
                }
            }

            json = jsonp_stringn_nocheck_own(value, len);
            if(json) {
                lex->value.string.val = NULL;
                lex->value.string.len = 0;
            }
            break;
        }

        case TOKEN_INTEGER: {
            json = json_integer(lex->value.integer);
            break;
        }

        case TOKEN_REAL: {
            json = json_real(lex->value.real);
            break;
        }

        case TOKEN_TRUE:
            json = json_true();
            break;

        case TOKEN_FALSE:
            json = json_false();
            break;

        case TOKEN_NULL:
            json = json_null();
            break;

        case '{':
            json = parse_object(lex, flags, error);
            break;

        case '[':
            json = parse_array(lex, flags, error);
            break;

        case TOKEN_INVALID:
            error_set(error, lex, "invalid token");
            return NULL;

        default:
            error_set(error, lex, "unexpected token");
            return NULL;
    }

    if(!json)
        return NULL;

    lex->depth--;
    return json;
}