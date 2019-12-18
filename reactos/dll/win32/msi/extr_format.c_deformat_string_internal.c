#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/ * deformatted; int /*<<< orphan*/  groups; int /*<<< orphan*/  n; int /*<<< orphan*/  propfailed; int /*<<< orphan*/ * record; int /*<<< orphan*/ * package; } ;
struct TYPE_10__ {int len; int type; } ;
typedef  int /*<<< orphan*/  STACK ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ FORMSTR ;
typedef  TYPE_2__ FORMAT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int FORMAT_ESCAPE ; 
 int FORMAT_LBRACE ; 
 int FORMAT_LBRACK ; 
 int FORMAT_LITERAL ; 
 int FORMAT_NULL ; 
 int FORMAT_NUMBER ; 
 int FORMAT_PROPNULL ; 
 int FORMAT_RBRACE ; 
 int FORMAT_RBRACK ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * create_stack () ; 
 int format_lex (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  free_stack (int /*<<< orphan*/ *) ; 
 int left_type (int) ; 
 scalar_t__ lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  replace_stack (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stack_find (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_format (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD deformat_string_internal(MSIPACKAGE *package, LPCWSTR ptr, 
                                      WCHAR** data, DWORD *len,
                                      MSIRECORD* record)
{
    FORMAT format;
    FORMSTR *str = NULL;
    STACK *stack, *temp;
    FORMSTR *node;
    int type;

    if (!ptr)
    {
        *data = NULL;
        *len = 0;
        return ERROR_SUCCESS;
    }

    *data = strdupW(ptr);
    *len = lstrlenW(ptr);

    ZeroMemory(&format, sizeof(FORMAT));
    format.package = package;
    format.record = record;
    format.deformatted = *data;
    format.len = *len;

    if (!verify_format(*data))
        return ERROR_SUCCESS;

    stack = create_stack();
    temp = create_stack();

    while ((type = format_lex(&format, &str)) != FORMAT_NULL)
    {
        if (type == FORMAT_LBRACK || type == FORMAT_LBRACE ||
            type == FORMAT_LITERAL || type == FORMAT_NUMBER ||
            type == FORMAT_ESCAPE || type == FORMAT_PROPNULL)
        {
            if (type == FORMAT_LBRACE)
            {
                format.propfailed = FALSE;
                format.groups++;
            }
            else if (type == FORMAT_ESCAPE &&
                     !stack_find(stack, FORMAT_LBRACK))
            {
                format.n -= str->len - 1;
                str->len = 1;
            }

            stack_push(stack, str);
        }
        else if (type == FORMAT_RBRACK || type == FORMAT_RBRACE)
        {
            if (type == FORMAT_RBRACE)
                format.groups--;

            stack_push(stack, str);

            if (stack_find(stack, left_type(type)))
            {
                do
                {
                    node = stack_pop(stack);
                    stack_push(temp, node);
                } while (node->type != left_type(type));

                replace_stack(&format, stack, temp);
            }
        }
    }

    *data = format.deformatted;
    *len = format.len;

    msi_free(str);
    free_stack(stack);
    free_stack(temp);

    return ERROR_SUCCESS;
}