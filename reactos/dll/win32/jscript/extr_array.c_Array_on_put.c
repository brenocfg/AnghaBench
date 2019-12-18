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
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int WCHAR ;
struct TYPE_3__ {int length; } ;
typedef  int DWORD ;
typedef  TYPE_1__ ArrayInstance ;

/* Variables and functions */
 TYPE_1__* array_from_jsdisp (int /*<<< orphan*/ *) ; 
 scalar_t__ iswdigit (int const) ; 

__attribute__((used)) static void Array_on_put(jsdisp_t *dispex, const WCHAR *name)
{
    ArrayInstance *array = array_from_jsdisp(dispex);
    const WCHAR *ptr = name;
    DWORD id = 0;

    if(!iswdigit(*ptr))
        return;

    while(*ptr && iswdigit(*ptr)) {
        id = id*10 + (*ptr-'0');
        ptr++;
    }

    if(*ptr)
        return;

    if(id >= array->length)
        array->length = id+1;
}