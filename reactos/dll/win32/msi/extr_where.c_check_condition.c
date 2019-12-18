#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {size_t table_index; scalar_t__ row_count; } ;
struct TYPE_7__ {int /*<<< orphan*/  cond; scalar_t__ rec_index; } ;
typedef  TYPE_1__ MSIWHEREVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_2__ JOINTABLE ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ ERROR_CONTINUE ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ INVALID_ROW_INDEX ; 
 scalar_t__ WHERE_evaluate (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_row (TYPE_1__*,scalar_t__*) ; 

__attribute__((used)) static UINT check_condition( MSIWHEREVIEW *wv, MSIRECORD *record, JOINTABLE **tables,
                             UINT table_rows[] )
{
    UINT r = ERROR_FUNCTION_FAILED;
    INT val;

    for (table_rows[(*tables)->table_index] = 0;
         table_rows[(*tables)->table_index] < (*tables)->row_count;
         table_rows[(*tables)->table_index]++)
    {
        val = 0;
        wv->rec_index = 0;
        r = WHERE_evaluate( wv, table_rows, wv->cond, &val, record );
        if (r != ERROR_SUCCESS && r != ERROR_CONTINUE)
            break;
        if (val)
        {
            if (*(tables + 1))
            {
                r = check_condition(wv, record, tables + 1, table_rows);
                if (r != ERROR_SUCCESS)
                    break;
            }
            else
            {
                if (r != ERROR_SUCCESS)
                    break;
                add_row (wv, table_rows);
            }
        }
    }
    table_rows[(*tables)->table_index] = INVALID_ROW_INDEX;
    return r;
}