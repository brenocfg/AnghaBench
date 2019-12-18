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
struct chunk {int flags; int action; int /*<<< orphan*/  data; } ;

/* Variables and functions */
#define  ACTION_APPEND 138 
#define  ACTION_APPEND_SMALL 137 
#define  ACTION_APPLY_TPL 136 
#define  ACTION_END_IF_VARIABLE_NOT_EMPTY 135 
#define  ACTION_END_ITER 134 
#define  ACTION_IF_VARIABLE_NOT_EMPTY 133 
#define  ACTION_LAST 132 
#define  ACTION_START_ITER 131 
#define  ACTION_VARIABLE 130 
#define  ACTION_VARIABLE_STR 129 
#define  ACTION_VARIABLE_STR_ESCAPE 128 
 int FLAGS_NO_FREE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_strbuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_tpl_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_chunk(struct chunk *chunk)
{
    if (!chunk)
        return;
    if (chunk->flags & FLAGS_NO_FREE)
        return;

    switch (chunk->action) {
    case ACTION_LAST:
    case ACTION_APPEND_SMALL:
    case ACTION_VARIABLE:
    case ACTION_VARIABLE_STR:
    case ACTION_VARIABLE_STR_ESCAPE:
    case ACTION_END_IF_VARIABLE_NOT_EMPTY:
    case ACTION_END_ITER:
        /* do nothing */
        break;
    case ACTION_IF_VARIABLE_NOT_EMPTY:
    case ACTION_START_ITER:
        free(chunk->data);
        break;
    case ACTION_APPEND:
        lwan_strbuf_free(chunk->data);
        break;
    case ACTION_APPLY_TPL:
        lwan_tpl_free(chunk->data);
        break;
    }
}