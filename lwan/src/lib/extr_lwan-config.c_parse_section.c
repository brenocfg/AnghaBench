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
struct parser {int /*<<< orphan*/  items; int /*<<< orphan*/  strbuf; int /*<<< orphan*/  buffer; } ;
struct TYPE_2__ {size_t len; int /*<<< orphan*/  value; } ;
struct lexeme {TYPE_1__ value; } ;
struct config_line {int /*<<< orphan*/  value; int /*<<< orphan*/  key; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_LINE_TYPE_SECTION ; 
 scalar_t__ config_ring_buffer_try_put (int /*<<< orphan*/ *,struct config_line*) ; 
 int /*<<< orphan*/  lexeme_ring_buffer_empty (int /*<<< orphan*/ *) ; 
 struct lexeme* lexeme_ring_buffer_get_ptr_or_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_strbuf_append_char (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  lwan_strbuf_append_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  lwan_strbuf_get_buffer (int /*<<< orphan*/ *) ; 
 void* parse_config ; 

__attribute__((used)) static void *parse_section(struct parser *parser)
{
    const struct lexeme *lexeme;
    size_t name_len;

    if (!(lexeme = lexeme_ring_buffer_get_ptr_or_null(&parser->buffer)))
        return NULL;

    lwan_strbuf_append_str(&parser->strbuf, lexeme->value.value,
                           lexeme->value.len);
    name_len = lexeme->value.len;
    lwan_strbuf_append_char(&parser->strbuf, '\0');

    while ((lexeme = lexeme_ring_buffer_get_ptr_or_null(&parser->buffer))) {
        lwan_strbuf_append_str(&parser->strbuf, lexeme->value.value,
                               lexeme->value.len);

        if (!lexeme_ring_buffer_empty(&parser->buffer))
            lwan_strbuf_append_char(&parser->strbuf, ' ');
    }

    struct config_line line = {
        .type = CONFIG_LINE_TYPE_SECTION,
        .key = lwan_strbuf_get_buffer(&parser->strbuf),
        .value = lwan_strbuf_get_buffer(&parser->strbuf) + name_len + 1,
    };
    return config_ring_buffer_try_put(&parser->items, &line) ? parse_config
                                                             : NULL;
}