#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_6__ {int /*<<< orphan*/ * db; TYPE_1__ view; int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  MSIVIEW ;
typedef  TYPE_2__ MSIDROPVIEW ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ TABLE_CreateView (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_ops ; 
 TYPE_2__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_2__*) ; 

UINT DROP_CreateView(MSIDATABASE *db, MSIVIEW **view, LPCWSTR name)
{
    MSIDROPVIEW *dv;
    UINT r;

    TRACE("%p %s\n", view, debugstr_w(name));

    dv = msi_alloc_zero(sizeof *dv);
    if(!dv)
        return ERROR_FUNCTION_FAILED;

    r = TABLE_CreateView(db, name, &dv->table);
    if (r != ERROR_SUCCESS)
    {
        msi_free( dv );
        return r;
    }

    dv->view.ops = &drop_ops;
    dv->db = db;

    *view = (MSIVIEW *)dv;

    return ERROR_SUCCESS;
}