#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  column_info ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_17__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_19__ {TYPE_3__* sv; int /*<<< orphan*/  bIsTemp; int /*<<< orphan*/ * vals; TYPE_5__* db; TYPE_3__* table; TYPE_2__ view; } ;
struct TYPE_18__ {TYPE_1__* ops; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* delete ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ MSIVIEW ;
typedef  TYPE_4__ MSIINSERTVIEW ;
typedef  TYPE_5__ MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_BAD_QUERY_SYNTAX ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ SELECT_CreateView (TYPE_5__*,TYPE_3__**,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ TABLE_CreateView (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 scalar_t__ count_column_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_ops ; 
 TYPE_4__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msiobj_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

UINT INSERT_CreateView( MSIDATABASE *db, MSIVIEW **view, LPCWSTR table,
                        column_info *columns, column_info *values, BOOL temp )
{
    MSIINSERTVIEW *iv = NULL;
    UINT r;
    MSIVIEW *tv = NULL, *sv = NULL;

    TRACE("%p\n", iv );

    /* there should be one value for each column */
    if ( count_column_info( columns ) != count_column_info(values) )
        return ERROR_BAD_QUERY_SYNTAX;

    r = TABLE_CreateView( db, table, &tv );
    if( r != ERROR_SUCCESS )
        return r;

    r = SELECT_CreateView( db, &sv, tv, columns );
    if( r != ERROR_SUCCESS )
    {
        if( tv )
            tv->ops->delete( tv );
        return r;
    }

    iv = msi_alloc_zero( sizeof *iv );
    if( !iv )
        return ERROR_FUNCTION_FAILED;

    /* fill the structure */
    iv->view.ops = &insert_ops;
    msiobj_addref( &db->hdr );
    iv->table = tv;
    iv->db = db;
    iv->vals = values;
    iv->bIsTemp = temp;
    iv->sv = sv;
    *view = (MSIVIEW*) iv;

    return ERROR_SUCCESS;
}