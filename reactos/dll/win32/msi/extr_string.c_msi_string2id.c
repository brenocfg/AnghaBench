#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sortcount; size_t* sorted; TYPE_1__* strings; } ;
typedef  TYPE_2__ string_table ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 size_t ERROR_INVALID_PARAMETER ; 
 size_t ERROR_SUCCESS ; 
 int cmp_string (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 

UINT msi_string2id( const string_table *st, const WCHAR *str, int len, UINT *id )
{
    int i, c, low = 0, high = st->sortcount - 1;

    if (len < 0) len = strlenW( str );

    while (low <= high)
    {
        i = (low + high) / 2;
        c = cmp_string( str, len, st->strings[st->sorted[i]].data, st->strings[st->sorted[i]].len );

        if (c < 0)
            high = i - 1;
        else if (c > 0)
            low = i + 1;
        else
        {
            *id = st->sorted[i];
            return ERROR_SUCCESS;
        }
    }
    return ERROR_INVALID_PARAMETER;
}