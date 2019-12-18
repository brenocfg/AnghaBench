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
struct TYPE_3__ {char* pNextCharW; size_t next_arg; size_t argc; char** argv; } ;
typedef  TYPE_1__ context_t ;
typedef  char WCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */

__attribute__((used)) static WCHAR get_next_wchar(context_t * cx, BOOL use_next_parameter)
{
    WCHAR   c;

    /* Try the next WCHAR in the actual Parameter */
    if (cx->pNextCharW) {
        c = *cx->pNextCharW;
        if (c) {
            cx->pNextCharW++;
            return c;
        }
        /* We reached the end of the Parameter */
        cx->pNextCharW = NULL;
    }

    /* Get the next Parameter, when available and allowed */
    if ((cx->pNextCharW == NULL) && (cx->next_arg < cx->argc) && (use_next_parameter)) {
        cx->pNextCharW = cx->argv[cx->next_arg];
        cx->next_arg++;
    }

    if (cx->pNextCharW) {
        c = *cx->pNextCharW;
        if (c) {
            cx->pNextCharW++;
        }
        else
        {
            /* We reached the end of the Parameter */
            cx->pNextCharW = NULL;
        }
        return c;
    }
    return '\0';
}