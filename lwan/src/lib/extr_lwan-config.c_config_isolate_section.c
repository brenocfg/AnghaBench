#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lexer {char const* start; char const* pos; char const* end; } ;
struct config_line {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  strbuf; struct lexer lexer; } ;
struct TYPE_3__ {scalar_t__ sz; int /*<<< orphan*/ * addr; } ;
struct config {TYPE_2__ parser; TYPE_1__ mapped; } ;

/* Variables and functions */
 scalar_t__ CONFIG_LINE_TYPE_SECTION ; 
 int /*<<< orphan*/  config_error (struct config*,char*) ; 
 int /*<<< orphan*/  find_section_end (struct config*) ; 
 int /*<<< orphan*/  free (struct config*) ; 
 int /*<<< orphan*/  lwan_strbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_strbuf_init (int /*<<< orphan*/ *) ; 
 struct config* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct config*,struct config*,int) ; 

struct config *config_isolate_section(struct config *current_conf,
                                      const struct config_line *current_line)
{
    struct lexer *lexer;
    struct config *isolated;
    const char *pos;

    if (current_line->type != CONFIG_LINE_TYPE_SECTION)
        return NULL;

    isolated = malloc(sizeof(*isolated));
    if (!isolated)
        return NULL;

    memcpy(isolated, current_conf, sizeof(*isolated));
    lwan_strbuf_init(&isolated->parser.strbuf);

    isolated->mapped.addr = NULL;
    isolated->mapped.sz = 0;

    lexer = &isolated->parser.lexer;
    lexer->start = lexer->pos;

    pos = isolated->parser.lexer.pos;
    if (!find_section_end(isolated)) {
        lwan_strbuf_free(&isolated->parser.strbuf);
        free(isolated);

        config_error(current_conf,
                     "Could not find section end while trying to isolate");

        return NULL;
    }

    lexer->end = lexer->pos;
    lexer->start = lexer->pos = pos;

    return isolated;
}