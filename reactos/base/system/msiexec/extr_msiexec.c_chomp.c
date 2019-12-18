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
typedef  enum chomp_state { ____Placeholder_chomp_state } chomp_state ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  CS_QUOTE 130 
#define  CS_TOKEN 129 
#define  CS_WHITESPACE 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static int chomp( const WCHAR *in, WCHAR *out )
{
    enum chomp_state state = CS_TOKEN;
    const WCHAR *p;
    int count = 1;
    BOOL ignore;

    for (p = in; *p; p++)
    {
        ignore = TRUE;
        switch (state)
        {
        case CS_WHITESPACE:
            switch (*p)
            {
            case ' ':
                break;
            case '"':
                state = CS_QUOTE;
                count++;
                break;
            default:
                count++;
                ignore = FALSE;
                state = CS_TOKEN;
            }
            break;

        case CS_TOKEN:
            switch (*p)
            {
            case '"':
                state = CS_QUOTE;
                break;
            case ' ':
                state = CS_WHITESPACE;
                if (out) *out++ = 0;
                break;
            default:
                if (p > in && p[-1] == '"')
                {
                    if (out) *out++ = 0;
                    count++;
                }
                ignore = FALSE;
            }
            break;

        case CS_QUOTE:
            switch (*p)
            {
            case '"':
                state = CS_TOKEN;
                break;
            default:
                ignore = FALSE;
            }
            break;
        }
        if (!ignore && out) *out++ = *p;
    }
    if (out) *out = 0;
    return count;
}