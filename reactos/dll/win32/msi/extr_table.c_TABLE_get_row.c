#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  db; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ MSITABLEVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  msi_view_get_row (int /*<<< orphan*/ ,struct tagMSIVIEW*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT TABLE_get_row( struct tagMSIVIEW *view, UINT row, MSIRECORD **rec )
{
    MSITABLEVIEW *tv = (MSITABLEVIEW *)view;

    if (!tv->table)
        return ERROR_INVALID_PARAMETER;

    return msi_view_get_row(tv->db, view, row, rec);
}