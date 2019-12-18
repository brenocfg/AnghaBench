#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {TYPE_1__* ops; } ;
struct TYPE_15__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_14__ {scalar_t__* cols; TYPE_4__* table; } ;
struct TYPE_13__ {scalar_t__ (* get_row ) (TYPE_4__*,scalar_t__,TYPE_3__**) ;scalar_t__ (* modify ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ;} ;
typedef  TYPE_2__ MSISELECTVIEW ;
typedef  TYPE_3__ MSIRECORD ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIMODIFY_UPDATE ; 
 scalar_t__ MSITYPE_IS_BINARY (scalar_t__) ; 
 scalar_t__ MSITYPE_STRING ; 
 scalar_t__ MSI_RecordGetInteger (TYPE_3__*,scalar_t__) ; 
 scalar_t__ MSI_RecordSetInteger (TYPE_3__*,scalar_t__,scalar_t__) ; 
 scalar_t__ SELECT_get_column_info (struct tagMSIVIEW*,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SELECT_get_dimensions (struct tagMSIVIEW*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  msi_record_get_string (TYPE_3__*,scalar_t__,int*) ; 
 scalar_t__ msi_record_set_string (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_4__*,scalar_t__,TYPE_3__**) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static UINT msi_select_update(struct tagMSIVIEW *view, MSIRECORD *rec, UINT row)
{
    MSISELECTVIEW *sv = (MSISELECTVIEW*)view;
    UINT r, i, num_columns, col, type, val;
    LPCWSTR str;
    MSIRECORD *mod;

    r = SELECT_get_dimensions(view, NULL, &num_columns);
    if (r != ERROR_SUCCESS)
        return r;

    r = sv->table->ops->get_row(sv->table, row - 1, &mod);
    if (r != ERROR_SUCCESS)
        return r;

    for (i = 0; i < num_columns; i++)
    {
        col = sv->cols[i];

        r = SELECT_get_column_info(view, i + 1, NULL, &type, NULL, NULL);
        if (r != ERROR_SUCCESS)
        {
            ERR("Failed to get column information: %d\n", r);
            goto done;
        }

        if (MSITYPE_IS_BINARY(type))
        {
            ERR("Cannot modify binary data!\n");
            r = ERROR_FUNCTION_FAILED;
            goto done;
        }
        else if (type & MSITYPE_STRING)
        {
            int len;
            str = msi_record_get_string( rec, i + 1, &len );
            r = msi_record_set_string( mod, col, str, len );
        }
        else
        {
            val = MSI_RecordGetInteger(rec, i + 1);
            r = MSI_RecordSetInteger(mod, col, val);
        }

        if (r != ERROR_SUCCESS)
        {
            ERR("Failed to modify record: %d\n", r);
            goto done;
        }
    }

    r = sv->table->ops->modify(sv->table, MSIMODIFY_UPDATE, mod, row);

done:
    msiobj_release(&mod->hdr);
    return r;
}