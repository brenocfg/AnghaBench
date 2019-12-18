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
struct parser {int /*<<< orphan*/  items; } ;
struct config_line {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_LINE_TYPE_SECTION_END ; 
 scalar_t__ config_ring_buffer_try_put (int /*<<< orphan*/ *,struct config_line*) ; 
 void* parse_section (struct parser*) ; 

__attribute__((used)) static void *parse_section_shorthand(struct parser *parser)
{
    void *next_state = parse_section(parser);

    if (next_state) {
        struct config_line line = {.type = CONFIG_LINE_TYPE_SECTION_END};

        if (config_ring_buffer_try_put(&parser->items, &line))
            return next_state;
    }

    return NULL;
}