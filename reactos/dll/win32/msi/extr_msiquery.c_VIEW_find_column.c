#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {scalar_t__ (* get_dimensions ) (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__*) ;scalar_t__ (* get_column_info ) (TYPE_2__*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ;} ;
typedef  TYPE_2__ MSIVIEW ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  strcmpW (scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ stub2 (TYPE_2__*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

UINT VIEW_find_column( MSIVIEW *table, LPCWSTR name, LPCWSTR table_name, UINT *n )
{
    LPCWSTR col_name, haystack_table_name;
    UINT i, count, r;

    r = table->ops->get_dimensions( table, NULL, &count );
    if( r != ERROR_SUCCESS )
        return r;

    for( i=1; i<=count; i++ )
    {
        INT x;

        r = table->ops->get_column_info( table, i, &col_name, NULL,
                                         NULL, &haystack_table_name );
        if( r != ERROR_SUCCESS )
            return r;
        x = strcmpW( name, col_name );
        if( table_name )
            x |= strcmpW( table_name, haystack_table_name );
        if( !x )
        {
            *n = i;
            return ERROR_SUCCESS;
        }
    }
    return ERROR_INVALID_PARAMETER;
}