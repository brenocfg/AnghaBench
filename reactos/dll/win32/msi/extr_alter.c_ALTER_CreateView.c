#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ column_info ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_12__ {int hold; TYPE_2__ view; TYPE_1__* colinfo; int /*<<< orphan*/ * db; int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ MSIVIEW ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  TYPE_3__ MSIALTERVIEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ TABLE_CreateView (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__**,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  alter_ops ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 TYPE_3__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_3__*) ; 

UINT ALTER_CreateView( MSIDATABASE *db, MSIVIEW **view, LPCWSTR name, column_info *colinfo, int hold )
{
    MSIALTERVIEW *av;
    UINT r;

    TRACE("%p %p %s %d\n", view, colinfo, debugstr_w(name), hold );

    av = msi_alloc_zero( sizeof *av );
    if( !av )
        return ERROR_FUNCTION_FAILED;

    r = TABLE_CreateView( db, name, &av->table );
    if (r != ERROR_SUCCESS)
    {
        msi_free( av );
        return r;
    }

    if (colinfo)
        colinfo->table = name;

    /* fill the structure */
    av->view.ops = &alter_ops;
    av->db = db;
    av->hold = hold;
    av->colinfo = colinfo;

    *view = &av->view;

    return ERROR_SUCCESS;
}