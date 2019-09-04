#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* start; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  bstr_xappend (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_input_append_key_name (TYPE_1__*,int const) ; 

char *mp_input_get_key_combo_name(const int *keys, int max)
{
    bstr dst = {0};
    while (max > 0) {
        mp_input_append_key_name(&dst, *keys);
        if (--max && *++keys)
            bstr_xappend(NULL, &dst, bstr0("-"));
        else
            break;
    }
    return dst.start;
}