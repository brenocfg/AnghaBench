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
typedef  size_t UINT ;
struct TYPE_5__ {size_t num_cols; int /*<<< orphan*/  view; TYPE_1__* columns; } ;
struct TYPE_4__ {int type; } ;
typedef  TYPE_2__ MSITABLEVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 size_t ERROR_FUNCTION_FAILED ; 
 size_t ERROR_SUCCESS ; 
 int MSITYPE_KEY ; 
 size_t TABLE_fetch_int (int /*<<< orphan*/ *,size_t,size_t,size_t*) ; 

__attribute__((used)) static UINT msi_row_matches( MSITABLEVIEW *tv, UINT row, const UINT *data, UINT *column )
{
    UINT i, r, x, ret = ERROR_FUNCTION_FAILED;

    for( i=0; i<tv->num_cols; i++ )
    {
        if ( ~tv->columns[i].type & MSITYPE_KEY )
            continue;

        /* turn the transform column value into a row value */
        r = TABLE_fetch_int( &tv->view, row, i+1, &x );
        if ( r != ERROR_SUCCESS )
        {
            ERR("TABLE_fetch_int shouldn't fail here\n");
            break;
        }

        /* if this key matches, move to the next column */
        if ( x != data[i] )
        {
            ret = ERROR_FUNCTION_FAILED;
            break;
        }
        if (column) *column = i;
        ret = ERROR_SUCCESS;
    }
    return ret;
}