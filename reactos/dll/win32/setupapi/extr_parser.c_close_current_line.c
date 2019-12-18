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
struct parser {struct line* line; } ;
struct line {int nb_fields; int key_field; int first_field; } ;

/* Variables and functions */

__attribute__((used)) static void close_current_line( struct parser *parser )
{
    struct line *cur_line = parser->line;

    if (cur_line)
    {
        /* if line has a single field and no key, the field is the key too */
        if (cur_line->nb_fields == 1 && cur_line->key_field == -1)
            cur_line->key_field = cur_line->first_field;
    }
    parser->line = NULL;
}