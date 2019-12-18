#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char token; int column; scalar_t__ pos; scalar_t__ line; } ;
struct TYPE_5__ {char* fmt; int column; scalar_t__ pos; TYPE_1__ token; scalar_t__ line; TYPE_1__ next_token; TYPE_1__ prev_token; } ;
typedef  TYPE_2__ scanner_t ;

/* Variables and functions */

__attribute__((used)) static void next_token(scanner_t *s)
{
    const char *t;
    s->prev_token = s->token;

    if(s->next_token.line) {
        s->token = s->next_token;
        s->next_token.line = 0;
        return;
    }

    t = s->fmt;
    s->column++;
    s->pos++;

    /* skip space and ignored chars */
    while(*t == ' ' || *t == '\t' || *t == '\n' || *t == ',' || *t == ':') {
        if(*t == '\n') {
            s->line++;
            s->column = 1;
        }
        else
            s->column++;

        s->pos++;
        t++;
    }

    s->token.token = *t;
    s->token.line = s->line;
    s->token.column = s->column;
    s->token.pos = s->pos;

    t++;
    s->fmt = t;
}