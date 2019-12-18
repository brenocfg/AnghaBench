#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_12__ {TYPE_1__* ops; } ;
struct TYPE_11__ {size_t table_index; TYPE_4__* view; } ;
struct TYPE_10__ {int /*<<< orphan*/  tables; } ;
struct TYPE_9__ {scalar_t__ (* fetch_stream ) (TYPE_4__*,scalar_t__,scalar_t__,int /*<<< orphan*/ **) ;} ;
typedef  TYPE_2__ MSIWHEREVIEW ;
typedef  TYPE_3__ JOINTABLE ;
typedef  int /*<<< orphan*/  IStream ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ find_row (TYPE_2__*,scalar_t__,scalar_t__**) ; 
 TYPE_3__* find_table (TYPE_2__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ stub1 (TYPE_4__*,scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT WHERE_fetch_stream( struct tagMSIVIEW *view, UINT row, UINT col, IStream **stm )
{
    MSIWHEREVIEW *wv = (MSIWHEREVIEW*)view;
    JOINTABLE *table;
    UINT *rows;
    UINT r;

    TRACE("%p %d %d %p\n", wv, row, col, stm );

    if( !wv->tables )
        return ERROR_FUNCTION_FAILED;

    r = find_row(wv, row, &rows);
    if (r != ERROR_SUCCESS)
        return r;

    table = find_table(wv, col, &col);
    if (!table)
        return ERROR_FUNCTION_FAILED;

    return table->view->ops->fetch_stream( table->view, rows[table->table_index], col, stm );
}