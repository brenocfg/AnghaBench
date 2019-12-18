#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSITABLEVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ TABLE_delete_row (struct tagMSIVIEW*,scalar_t__) ; 
 scalar_t__ msi_table_find_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT modify_delete_row( struct tagMSIVIEW *view, MSIRECORD *rec )
{
    MSITABLEVIEW *tv = (MSITABLEVIEW *)view;
    UINT row, r;

    r = msi_table_find_row(tv, rec, &row, NULL);
    if (r != ERROR_SUCCESS)
        return r;

    return TABLE_delete_row(view, row);
}