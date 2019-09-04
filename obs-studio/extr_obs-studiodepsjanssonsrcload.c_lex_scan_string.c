#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* val; int len; } ;
struct TYPE_11__ {TYPE_1__ string; } ;
struct TYPE_13__ {scalar_t__ length; } ;
struct TYPE_12__ {int /*<<< orphan*/  token; TYPE_2__ value; TYPE_4__ saved_text; } ;
typedef  TYPE_3__ lex_t ;
typedef  int /*<<< orphan*/  json_error_t ;
typedef  int int32_t ;

/* Variables and functions */
 int STREAM_STATE_EOF ; 
 int STREAM_STATE_ERROR ; 
 int /*<<< orphan*/  TOKEN_INVALID ; 
 int /*<<< orphan*/  TOKEN_STRING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int decode_unicode_escape (char const*) ; 
 int /*<<< orphan*/  error_set (int /*<<< orphan*/ *,TYPE_3__*,char*,...) ; 
 char* jsonp_malloc (scalar_t__) ; 
 int /*<<< orphan*/  l_isxdigit (int) ; 
 int /*<<< orphan*/  lex_free_string (TYPE_3__*) ; 
 int lex_get_save (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_unget_unsave (TYPE_3__*,int) ; 
 char* strbuffer_value (TYPE_4__*) ; 
 scalar_t__ utf8_encode (int,char*,size_t*) ; 

__attribute__((used)) static void lex_scan_string(lex_t *lex, json_error_t *error)
{
    int c;
    const char *p;
    char *t;
    int i;

    lex->value.string.val = NULL;
    lex->token = TOKEN_INVALID;

    c = lex_get_save(lex, error);

    while(c != '"') {
        if(c == STREAM_STATE_ERROR)
            goto out;

        else if(c == STREAM_STATE_EOF) {
            error_set(error, lex, "premature end of input");
            goto out;
        }

        else if(0 <= c && c <= 0x1F) {
            /* control character */
            lex_unget_unsave(lex, c);
            if(c == '\n')
                error_set(error, lex, "unexpected newline");
            else
                error_set(error, lex, "control character 0x%x", c);
            goto out;
        }

        else if(c == '\\') {
            c = lex_get_save(lex, error);
            if(c == 'u') {
                c = lex_get_save(lex, error);
                for(i = 0; i < 4; i++) {
                    if(!l_isxdigit(c)) {
                        error_set(error, lex, "invalid escape");
                        goto out;
                    }
                    c = lex_get_save(lex, error);
                }
            }
            else if(c == '"' || c == '\\' || c == '/' || c == 'b' ||
                    c == 'f' || c == 'n' || c == 'r' || c == 't')
                c = lex_get_save(lex, error);
            else {
                error_set(error, lex, "invalid escape");
                goto out;
            }
        }
        else
            c = lex_get_save(lex, error);
    }

    /* the actual value is at most of the same length as the source
       string, because:
         - shortcut escapes (e.g. "\t") (length 2) are converted to 1 byte
         - a single \uXXXX escape (length 6) is converted to at most 3 bytes
         - two \uXXXX escapes (length 12) forming an UTF-16 surrogate pair
           are converted to 4 bytes
    */
    t = jsonp_malloc(lex->saved_text.length + 1);
    if(!t) {
        /* this is not very nice, since TOKEN_INVALID is returned */
        goto out;
    }
    lex->value.string.val = t;

    /* + 1 to skip the " */
    p = strbuffer_value(&lex->saved_text) + 1;

    while(*p != '"') {
        if(*p == '\\') {
            p++;
            if(*p == 'u') {
                size_t length;
                int32_t value;

                value = decode_unicode_escape(p);
                if(value < 0) {
                    error_set(error, lex, "invalid Unicode escape '%.6s'", p - 1);
                    goto out;
                }
                p += 5;

                if(0xD800 <= value && value <= 0xDBFF) {
                    /* surrogate pair */
                    if(*p == '\\' && *(p + 1) == 'u') {
                        int32_t value2 = decode_unicode_escape(++p);
                        if(value2 < 0) {
                            error_set(error, lex, "invalid Unicode escape '%.6s'", p - 1);
                            goto out;
                        }
                        p += 5;

                        if(0xDC00 <= value2 && value2 <= 0xDFFF) {
                            /* valid second surrogate */
                            value =
                                ((value - 0xD800) << 10) +
                                (value2 - 0xDC00) +
                                0x10000;
                        }
                        else {
                            /* invalid second surrogate */
                            error_set(error, lex,
                                      "invalid Unicode '\\u%04X\\u%04X'",
                                      value, value2);
                            goto out;
                        }
                    }
                    else {
                        /* no second surrogate */
                        error_set(error, lex, "invalid Unicode '\\u%04X'",
                                  value);
                        goto out;
                    }
                }
                else if(0xDC00 <= value && value <= 0xDFFF) {
                    error_set(error, lex, "invalid Unicode '\\u%04X'", value);
                    goto out;
                }

                if(utf8_encode(value, t, &length))
                    assert(0);
                t += length;
            }
            else {
                switch(*p) {
                    case '"': case '\\': case '/':
                        *t = *p; break;
                    case 'b': *t = '\b'; break;
                    case 'f': *t = '\f'; break;
                    case 'n': *t = '\n'; break;
                    case 'r': *t = '\r'; break;
                    case 't': *t = '\t'; break;
                    default: assert(0);
                }
                t++;
                p++;
            }
        }
        else
            *(t++) = *(p++);
    }
    *t = '\0';
    lex->value.string.len = t - lex->value.string.val;
    lex->token = TOKEN_STRING;
    return;

out:
    lex_free_string(lex);
}