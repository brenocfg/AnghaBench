#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_15__ {scalar_t__ row_count; int /*<<< orphan*/ * translation; TYPE_3__* table; TYPE_5__* db; TYPE_2__ view; } ;
struct TYPE_14__ {TYPE_1__* ops; } ;
struct TYPE_12__ {scalar_t__ (* get_dimensions ) (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;} ;
typedef  TYPE_3__ MSIVIEW ;
typedef  TYPE_4__ MSIDISTINCTVIEW ;
typedef  TYPE_5__ MSIDATABASE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  distinct_ops ; 
 TYPE_4__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msiobj_addref (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ; 

UINT DISTINCT_CreateView( MSIDATABASE *db, MSIVIEW **view, MSIVIEW *table )
{
    MSIDISTINCTVIEW *dv = NULL;
    UINT count = 0, r;

    TRACE("%p\n", dv );

    r = table->ops->get_dimensions( table, NULL, &count );
    if( r != ERROR_SUCCESS )
    {
        ERR("can't get table dimensions\n");
        return r;
    }

    dv = msi_alloc_zero( sizeof *dv );
    if( !dv )
        return ERROR_FUNCTION_FAILED;
    
    /* fill the structure */
    dv->view.ops = &distinct_ops;
    msiobj_addref( &db->hdr );
    dv->db = db;
    dv->table = table;
    dv->translation = NULL;
    dv->row_count = 0;
    *view = (MSIVIEW*) dv;

    return ERROR_SUCCESS;
}