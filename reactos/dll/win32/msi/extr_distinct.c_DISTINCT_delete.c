#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {TYPE_1__* ops; } ;
struct TYPE_9__ {TYPE_2__* db; struct TYPE_9__* translation; TYPE_4__* table; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* delete ) (TYPE_4__*) ;} ;
typedef  TYPE_3__ MSIDISTINCTVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  msi_free (TYPE_3__*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static UINT DISTINCT_delete( struct tagMSIVIEW *view )
{
    MSIDISTINCTVIEW *dv = (MSIDISTINCTVIEW*)view;

    TRACE("%p\n", dv );

    if( dv->table )
        dv->table->ops->delete( dv->table );

    msi_free( dv->translation );
    msiobj_release( &dv->db->hdr );
    msi_free( dv );

    return ERROR_SUCCESS;
}