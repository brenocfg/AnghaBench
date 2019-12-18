#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  token_t ;
struct TYPE_3__ {size_t flags; char const* fmt; char const* start; int line; scalar_t__ pos; scalar_t__ column; int /*<<< orphan*/  next_token; int /*<<< orphan*/  token; int /*<<< orphan*/  prev_token; int /*<<< orphan*/ * error; } ;
typedef  TYPE_1__ scanner_t ;
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void scanner_init(scanner_t *s, json_error_t *error,
                         size_t flags, const char *fmt)
{
    s->error = error;
    s->flags = flags;
    s->fmt = s->start = fmt;
    memset(&s->prev_token, 0, sizeof(token_t));
    memset(&s->token, 0, sizeof(token_t));
    memset(&s->next_token, 0, sizeof(token_t));
    s->line = 1;
    s->column = 0;
    s->pos = 0;
}