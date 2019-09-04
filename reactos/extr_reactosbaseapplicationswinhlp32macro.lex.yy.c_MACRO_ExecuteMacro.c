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
struct lex_data {int cache_used; int /*<<< orphan*/ * cache_string; int /*<<< orphan*/  window; int /*<<< orphan*/  macroptr; } ;
typedef  int /*<<< orphan*/  WINHELP_WINDOW ;
struct TYPE_2__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  function; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  BOOL_FUNCTION 130 
#define  EMPTY 129 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACRO_CallVoidFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  VOID_FUNCTION 128 
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINHELP_GrabWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINHELP_ReleaseWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  YY_FLUSH_BUFFER ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 
 struct lex_data* lex_data ; 
 int /*<<< orphan*/  memset (struct lex_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts (int) ; 
 int yylex () ; 
 TYPE_1__ yylval ; 

BOOL MACRO_ExecuteMacro(WINHELP_WINDOW* window, LPCSTR macro)
{
    struct lex_data     curr_lex_data, *prev_lex_data;
    BOOL ret = TRUE;
    int t;

    WINE_TRACE("%s\n", debugstr_a(macro));

    prev_lex_data = lex_data;
    lex_data = &curr_lex_data;

    memset(lex_data, 0, sizeof(*lex_data));
    lex_data->macroptr = macro;
    lex_data->window = WINHELP_GrabWindow(window);

    while ((t = yylex()) != EMPTY)
    {
        switch (t)
        {
        case VOID_FUNCTION:
            WINE_TRACE("got type void func(%s)\n", debugstr_a(yylval.proto));
            MACRO_CallVoidFunc(yylval.function, yylval.proto);
            break;
        case BOOL_FUNCTION:
            WINE_WARN("got type bool func(%s)\n", debugstr_a(yylval.proto));
            break;
        default:
            WINE_WARN("got unexpected type %s\n", debugstr_a(ts(t)));
            YY_FLUSH_BUFFER;
            ret = FALSE;
            goto done;
        }
        switch (t = yylex())
        {
        case EMPTY:     goto done;
        case ';':       break;
        default:        ret = FALSE; YY_FLUSH_BUFFER; goto done;
        }
    }

done:
    for (t = 0; t < lex_data->cache_used; t++)
        HeapFree(GetProcessHeap(), 0, lex_data->cache_string[t]);
    lex_data = prev_lex_data;
    WINHELP_ReleaseWindow(window);

    return ret;
}