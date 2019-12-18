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
struct parser {int /*<<< orphan*/ * value_name; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_START ; 
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_xalloc (int) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unescape_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static WCHAR *quoted_value_name_state(struct parser *parser, WCHAR *pos)
{
    WCHAR *val_name = pos, *p;

    if (parser->value_name)
    {
        heap_free(parser->value_name);
        parser->value_name = NULL;
    }

    if (!unescape_string(val_name, &p))
        goto invalid;

    /* copy the value name in case we need to parse multiple lines and the buffer is overwritten */
    parser->value_name = heap_xalloc((lstrlenW(val_name) + 1) * sizeof(WCHAR));
    lstrcpyW(parser->value_name, val_name);

    set_state(parser, DATA_START);
    return p;

invalid:
    set_state(parser, LINE_START);
    return val_name;
}