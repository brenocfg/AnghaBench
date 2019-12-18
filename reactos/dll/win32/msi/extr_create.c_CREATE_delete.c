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
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {TYPE_1__* db; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_2__ MSICREATEVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  msi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT CREATE_delete( struct tagMSIVIEW *view )
{
    MSICREATEVIEW *cv = (MSICREATEVIEW*)view;

    TRACE("%p\n", cv );

    msiobj_release( &cv->db->hdr );
    msi_free( cv );

    return ERROR_SUCCESS;
}