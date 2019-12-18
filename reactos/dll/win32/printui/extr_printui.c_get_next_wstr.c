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
struct TYPE_3__ {size_t next_arg; size_t argc; scalar_t__* pNextCharW; scalar_t__** argv; } ;
typedef  TYPE_1__ context_t ;
typedef  scalar_t__* LPWSTR ;

/* Variables and functions */

__attribute__((used)) static LPWSTR get_next_wstr(context_t * cx)
{
    LPWSTR  ptr;

    ptr = cx->pNextCharW;
    if (ptr && ptr[0]) {
        cx->pNextCharW = NULL;
        return ptr;
    }

    /* Get the next Parameter, when available */
    if (cx->next_arg < cx->argc) {
        ptr = cx->argv[cx->next_arg];
        cx->next_arg++;
        cx->pNextCharW = NULL;
        return ptr;
    }
    return NULL;
}