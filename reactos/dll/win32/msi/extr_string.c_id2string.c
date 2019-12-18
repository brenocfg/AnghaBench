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
struct TYPE_4__ {int /*<<< orphan*/  codepage; int /*<<< orphan*/  maxcount; } ;
typedef  TYPE_1__ string_table ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;

/* Variables and functions */
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_MORE_DATA ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_string_lookup (TYPE_1__ const*,int,int*) ; 

__attribute__((used)) static UINT id2string( const string_table *st, UINT id, char *buffer, UINT *sz )
{
    int len, lenW;
    const WCHAR *str;

    TRACE("Finding string %d of %d\n", id, st->maxcount);

    str = msi_string_lookup( st, id, &lenW );
    if( !str )
        return ERROR_FUNCTION_FAILED;

    len = WideCharToMultiByte( st->codepage, 0, str, lenW, NULL, 0, NULL, NULL );
    if( *sz < len )
    {
        *sz = len;
        return ERROR_MORE_DATA;
    }
    *sz = WideCharToMultiByte( st->codepage, 0, str, lenW, buffer, *sz, NULL, NULL );
    return ERROR_SUCCESS;
}