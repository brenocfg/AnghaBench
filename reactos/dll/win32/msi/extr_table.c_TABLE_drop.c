#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {size_t col_count; int /*<<< orphan*/  entry; TYPE_1__* colinfo; } ;
struct TYPE_18__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_17__ {TYPE_9__* table; int /*<<< orphan*/  db; int /*<<< orphan*/  name; } ;
struct TYPE_16__ {TYPE_2__* ops; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* delete ) (TYPE_3__*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  number; int /*<<< orphan*/  tablename; } ;
typedef  TYPE_3__ MSIVIEW ;
typedef  TYPE_4__ MSITABLEVIEW ;
typedef  TYPE_5__ MSIRECORD ;
typedef  size_t INT ;

/* Variables and functions */
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 TYPE_5__* MSI_CreateRecord (int) ; 
 int /*<<< orphan*/  MSI_RecordSetStringW (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TABLE_CreateView (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 scalar_t__ TABLE_delete_row (TYPE_3__*,scalar_t__) ; 
 scalar_t__ TABLE_remove_column (struct tagMSIVIEW*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_table (TYPE_9__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 scalar_t__ msi_table_find_row (TYPE_4__*,TYPE_5__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  szTables ; 

__attribute__((used)) static UINT TABLE_drop(struct tagMSIVIEW *view)
{
    MSITABLEVIEW *tv = (MSITABLEVIEW*)view;
    MSIVIEW *tables = NULL;
    MSIRECORD *rec = NULL;
    UINT r, row;
    INT i;

    TRACE("dropping table %s\n", debugstr_w(tv->name));

    for (i = tv->table->col_count - 1; i >= 0; i--)
    {
        r = TABLE_remove_column(view, tv->table->colinfo[i].tablename,
                                tv->table->colinfo[i].number);
        if (r != ERROR_SUCCESS)
            return r;
    }

    rec = MSI_CreateRecord(1);
    if (!rec)
        return ERROR_OUTOFMEMORY;

    MSI_RecordSetStringW(rec, 1, tv->name);

    r = TABLE_CreateView(tv->db, szTables, &tables);
    if (r != ERROR_SUCCESS)
    {
        msiobj_release(&rec->hdr);
        return r;
    }

    r = msi_table_find_row((MSITABLEVIEW *)tables, rec, &row, NULL);
    if (r != ERROR_SUCCESS)
        goto done;

    r = TABLE_delete_row(tables, row);
    if (r != ERROR_SUCCESS)
        goto done;

    list_remove(&tv->table->entry);
    free_table(tv->table);

done:
    msiobj_release(&rec->hdr);
    tables->ops->delete(tables);

    return r;
}