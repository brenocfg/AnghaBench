#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_16__ {int type; } ;
struct TYPE_15__ {scalar_t__ package; void* propfailed; scalar_t__ record; } ;
struct TYPE_14__ {int n; int len; int type; } ;
typedef  int /*<<< orphan*/  STACK ;
typedef  TYPE_1__ FORMSTR ;
typedef  TYPE_2__ FORMAT ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int FORMAT_ESCAPE ; 
 int FORMAT_LITERAL ; 
 int FORMAT_NUMBER ; 
 void* TRUE ; 
 int /*<<< orphan*/ * deformat_index (TYPE_2__*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * deformat_literal (TYPE_2__*,TYPE_1__*,void**,int*,int*) ; 
 int /*<<< orphan*/ * dup_formstr (TYPE_2__*,TYPE_1__*,int*) ; 
 scalar_t__ format_str_is_number (int /*<<< orphan*/ *) ; 
 TYPE_1__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 
 TYPE_4__* stack_peek (int /*<<< orphan*/ *) ; 
 TYPE_1__* stack_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *replace_stack_prop( FORMAT *format, STACK *values,
                                  BOOL *propfound, BOOL *nonprop,
                                  int *oldsize, int *type, int *len )
{
    WCHAR *replaced;
    FORMSTR *content, *node;
    int n;

    *propfound = FALSE;
    *nonprop = FALSE;

    node = stack_pop(values);
    n = node->n;
    *oldsize = node->len;
    *type = stack_peek(values)->type;
    msi_free(node);

    while ((node = stack_pop(values)))
    {
        *oldsize += node->len;

        if (*type != FORMAT_ESCAPE &&
            stack_peek(values) && node->type != *type)
            *type = FORMAT_LITERAL;

        msi_free(node);
    }

    content = msi_alloc_zero(sizeof(FORMSTR));
    content->n = n + 1;
    content->len = *oldsize - 2;
    content->type = *type;

    if (*type == FORMAT_NUMBER && format->record)
    {
        replaced = deformat_index( format, content, len );
        if (replaced)
            *propfound = TRUE;
        else
            format->propfailed = TRUE;

        if (replaced)
            *type = format_str_is_number(replaced) ?
                FORMAT_NUMBER : FORMAT_LITERAL;
    }
    else if (format->package)
    {
        replaced = deformat_literal( format, content, propfound, type, len );
    }
    else
    {
        *nonprop = TRUE;
        content->n--;
        content->len += 2;
        replaced = dup_formstr( format, content, len );
    }
    msi_free(content);
    return replaced;
}