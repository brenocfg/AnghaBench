#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {TYPE_1__* ops; } ;
struct TYPE_7__ {TYPE_3__* table; } ;
struct TYPE_6__ {scalar_t__ (* get_dimensions ) (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;scalar_t__ (* get_column_info ) (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_2__ MSIINSERTVIEW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MSITYPE_KEY ; 
 scalar_t__ MSI_RecordIsNull (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ stub2 (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL row_has_null_primary_keys(MSIINSERTVIEW *iv, MSIRECORD *row)
{
    UINT r, i, col_count, type;

    r = iv->table->ops->get_dimensions( iv->table, NULL, &col_count );
    if (r != ERROR_SUCCESS)
        return FALSE;

    for (i = 1; i <= col_count; i++)
    {
        r = iv->table->ops->get_column_info(iv->table, i, NULL, &type,
                                            NULL, NULL);
        if (r != ERROR_SUCCESS)
            return FALSE;

        if (!(type & MSITYPE_KEY))
            continue;

        if (MSI_RecordIsNull(row, i))
            return TRUE;
    }

    return FALSE;
}