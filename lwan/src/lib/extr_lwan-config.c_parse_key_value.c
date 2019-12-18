#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parser {int /*<<< orphan*/  items; int /*<<< orphan*/  strbuf; int /*<<< orphan*/  lexer; int /*<<< orphan*/  buffer; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  value; } ;
struct lexeme {int type; TYPE_1__ value; } ;
struct config_line {int /*<<< orphan*/  key; int /*<<< orphan*/  value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_LINE_TYPE_LINE ; 
#define  LEXEME_CLOSE_BRACKET 133 
#define  LEXEME_EQUAL 132 
#define  LEXEME_LINEFEED 131 
#define  LEXEME_STRING 130 
#define  LEXEME_VARIABLE 129 
#define  LEXEME_VARIABLE_DEFAULT 128 
 int /*<<< orphan*/  backup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_ring_buffer_try_put (int /*<<< orphan*/ *,struct config_line*) ; 
 struct lexeme* lex_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lexeme_ring_buffer_empty (int /*<<< orphan*/ *) ; 
 struct lexeme* lexeme_ring_buffer_get_ptr_or_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lexeme_type_str ; 
 int /*<<< orphan*/  lwan_status_debug (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_status_error (char*,...) ; 
 int /*<<< orphan*/  lwan_strbuf_append_char (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  lwan_strbuf_append_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lwan_strbuf_append_strz (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lwan_strbuf_get_buffer (int /*<<< orphan*/ *) ; 
 size_t lwan_strbuf_get_length (int /*<<< orphan*/ *) ; 
 void* parse_config ; 
 char* secure_getenv_len (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void *parse_key_value(struct parser *parser)
{
    struct config_line line = {.type = CONFIG_LINE_TYPE_LINE};
    const struct lexeme *lexeme;
    size_t key_size;

    while ((lexeme = lexeme_ring_buffer_get_ptr_or_null(&parser->buffer))) {
        lwan_strbuf_append_str(&parser->strbuf, lexeme->value.value,
                               lexeme->value.len);

        if (!lexeme_ring_buffer_empty(&parser->buffer))
            lwan_strbuf_append_char(&parser->strbuf, '_');
    }
    key_size = lwan_strbuf_get_length(&parser->strbuf);
    lwan_strbuf_append_char(&parser->strbuf, '\0');

    while ((lexeme = lex_next(&parser->lexer))) {
        switch (lexeme->type) {
        case LEXEME_VARIABLE_DEFAULT:
        case LEXEME_VARIABLE: {
            const char *value;

            value = secure_getenv_len(lexeme->value.value, lexeme->value.len);
            if (lexeme->type == LEXEME_VARIABLE) {
                if (!value) {
                    lwan_status_error(
                        "Variable '$%.*s' not defined in environment",
                        (int)lexeme->value.len, lexeme->value.value);
                    return NULL;
                } else {
                    lwan_strbuf_append_strz(&parser->strbuf, value);
                }
            } else {
                const struct lexeme *var_name = lexeme;

                if (!(lexeme = lex_next(&parser->lexer))) {
                    lwan_status_error(
                        "Default value for variable '$%.*s' not given",
                        (int)var_name->value.len, var_name->value.value);
                    return NULL;
                }

                if (lexeme->type != LEXEME_STRING) {
                    lwan_status_error("Wrong format for default value");
                    return NULL;
                }

                if (!value) {
                    lwan_status_debug(
                        "Using default value of '%.*s' for variable '${%.*s}'",
                        (int)lexeme->value.len, lexeme->value.value,
                        (int)var_name->value.len, var_name->value.value);
                    lwan_strbuf_append_str(&parser->strbuf, lexeme->value.value,
                                           lexeme->value.len);
                } else {
                    lwan_strbuf_append_strz(&parser->strbuf, value);
                }
            }

            break;
        }

        case LEXEME_EQUAL:
            lwan_strbuf_append_char(&parser->strbuf, '=');
            break;

        case LEXEME_STRING:
            lwan_strbuf_append_str(&parser->strbuf, lexeme->value.value,
                                   lexeme->value.len);
            break;

        case LEXEME_CLOSE_BRACKET:
            backup(&parser->lexer);
            /* fallthrough */

        case LEXEME_LINEFEED:
            line.key = lwan_strbuf_get_buffer(&parser->strbuf);
            line.value = line.key + key_size + 1;
            return config_ring_buffer_try_put(&parser->items, &line)
                       ? parse_config
                       : NULL;

        default:
            lwan_status_error("Unexpected token while parsing key-value: %s",
                              lexeme_type_str[lexeme->type]);
            return NULL;
        }
    }

    lwan_status_error("EOF while parsing key-value");
    return NULL;
}