#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {TYPE_1__* ops; } ;
struct TYPE_18__ {scalar_t__ col_count; size_t table_index; TYPE_5__* view; struct TYPE_18__* next; } ;
struct TYPE_17__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_16__ {int col_count; TYPE_4__* tables; } ;
struct TYPE_15__ {scalar_t__ (* get_column_info ) (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ (* set_row ) (TYPE_5__*,scalar_t__,TYPE_3__*,scalar_t__) ;} ;
typedef  TYPE_2__ MSIWHEREVIEW ;
typedef  TYPE_3__ MSIRECORD ;
typedef  TYPE_4__ JOINTABLE ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSITYPE_KEY ; 
 TYPE_3__* MSI_CreateRecord (scalar_t__ const) ; 
 scalar_t__ MSI_RecordCopyField (TYPE_3__*,scalar_t__,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,scalar_t__,TYPE_3__*,scalar_t__) ; 
 scalar_t__ find_row (TYPE_2__*,scalar_t__,scalar_t__**) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_5__*,scalar_t__,TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static UINT WHERE_set_row( struct tagMSIVIEW *view, UINT row, MSIRECORD *rec, UINT mask )
{
    MSIWHEREVIEW *wv = (MSIWHEREVIEW*)view;
    UINT i, r, offset = 0;
    JOINTABLE *table = wv->tables;
    UINT *rows;
    UINT mask_copy = mask;

    TRACE("%p %d %p %08x\n", wv, row, rec, mask );

    if( !wv->tables )
         return ERROR_FUNCTION_FAILED;

    r = find_row(wv, row, &rows);
    if (r != ERROR_SUCCESS)
        return r;

    if (mask >= 1 << wv->col_count)
        return ERROR_INVALID_PARAMETER;

    do
    {
        for (i = 0; i < table->col_count; i++) {
            UINT type;

            if (!(mask_copy & (1 << i)))
                continue;
            r = table->view->ops->get_column_info(table->view, i + 1, NULL,
                                            &type, NULL, NULL );
            if (r != ERROR_SUCCESS)
                return r;
            if (type & MSITYPE_KEY)
                return ERROR_FUNCTION_FAILED;
        }
        mask_copy >>= table->col_count;
    }
    while (mask_copy && (table = table->next));

    table = wv->tables;

    do
    {
        const UINT col_count = table->col_count;
        UINT i;
        MSIRECORD *reduced;
        UINT reduced_mask = (mask >> offset) & ((1 << col_count) - 1);

        if (!reduced_mask)
        {
            offset += col_count;
            continue;
        }

        reduced = MSI_CreateRecord(col_count);
        if (!reduced)
            return ERROR_FUNCTION_FAILED;

        for (i = 1; i <= col_count; i++)
        {
            r = MSI_RecordCopyField(rec, i + offset, reduced, i);
            if (r != ERROR_SUCCESS)
                break;
        }

        offset += col_count;

        if (r == ERROR_SUCCESS)
            r = table->view->ops->set_row(table->view, rows[table->table_index], reduced, reduced_mask);

        msiobj_release(&reduced->hdr);
    }
    while ((table = table->next));
    return r;
}