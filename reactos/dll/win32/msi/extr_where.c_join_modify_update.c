#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_12__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_11__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIWHEREVIEW ;
typedef  TYPE_2__ MSIRECORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MSI_RecordGetFieldCount (TYPE_2__*) ; 
 int /*<<< orphan*/  MSI_RecordsAreFieldsEqual (TYPE_2__*,TYPE_2__*,scalar_t__) ; 
 scalar_t__ WHERE_set_row (struct tagMSIVIEW*,scalar_t__,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ join_find_row (TYPE_1__*,TYPE_2__*,scalar_t__*) ; 
 scalar_t__ msi_view_get_row (int /*<<< orphan*/ ,struct tagMSIVIEW*,scalar_t__,TYPE_2__**) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT join_modify_update( struct tagMSIVIEW *view, MSIRECORD *rec )
{
    MSIWHEREVIEW *wv = (MSIWHEREVIEW *)view;
    UINT r, row, i, mask = 0;
    MSIRECORD *current;


    r = join_find_row( wv, rec, &row );
    if (r != ERROR_SUCCESS)
        return r;

    r = msi_view_get_row( wv->db, view, row, &current );
    if (r != ERROR_SUCCESS)
        return r;

    assert(MSI_RecordGetFieldCount(rec) == MSI_RecordGetFieldCount(current));

    for (i = MSI_RecordGetFieldCount(rec); i > 0; i--)
    {
        if (!MSI_RecordsAreFieldsEqual(rec, current, i))
            mask |= 1 << (i - 1);
    }
     msiobj_release(&current->hdr);

    return WHERE_set_row( view, row, rec, mask );
}