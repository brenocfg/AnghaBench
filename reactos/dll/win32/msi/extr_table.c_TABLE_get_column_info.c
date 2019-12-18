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
struct tagMSIVIEW {int dummy; } ;
typedef  int UINT ;
struct TYPE_5__ {int num_cols; TYPE_1__* columns; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  temporary; int /*<<< orphan*/  tablename; int /*<<< orphan*/  colname; } ;
typedef  TYPE_2__ MSITABLEVIEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static UINT TABLE_get_column_info( struct tagMSIVIEW *view,
                UINT n, LPCWSTR *name, UINT *type, BOOL *temporary,
                LPCWSTR *table_name )
{
    MSITABLEVIEW *tv = (MSITABLEVIEW*)view;

    TRACE("%p %d %p %p\n", tv, n, name, type );

    if( ( n == 0 ) || ( n > tv->num_cols ) )
        return ERROR_INVALID_PARAMETER;

    if( name )
    {
        *name = tv->columns[n-1].colname;
        if( !*name )
            return ERROR_FUNCTION_FAILED;
    }

    if( table_name )
    {
        *table_name = tv->columns[n-1].tablename;
        if( !*table_name )
            return ERROR_FUNCTION_FAILED;
    }

    if( type )
        *type = tv->columns[n-1].type;

    if( temporary )
        *temporary = tv->columns[n-1].temporary;

    return ERROR_SUCCESS;
}