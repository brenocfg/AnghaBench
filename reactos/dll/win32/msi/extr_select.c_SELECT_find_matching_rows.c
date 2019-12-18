#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int UINT ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int num_cols; int* cols; TYPE_3__* table; } ;
struct TYPE_4__ {int (* find_matching_rows ) (TYPE_3__*,int,int,int*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ MSISELECTVIEW ;
typedef  int /*<<< orphan*/  MSIITERHANDLE ;

/* Variables and functions */
 int ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int,int,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT SELECT_find_matching_rows( struct tagMSIVIEW *view, UINT col,
    UINT val, UINT *row, MSIITERHANDLE *handle )
{
    MSISELECTVIEW *sv = (MSISELECTVIEW*)view;

    TRACE("%p, %d, %u, %p\n", view, col, val, *handle);

    if( !sv->table )
         return ERROR_FUNCTION_FAILED;

    if( (col==0) || (col>sv->num_cols) )
         return ERROR_FUNCTION_FAILED;

    col = sv->cols[ col - 1 ];

    return sv->table->ops->find_matching_rows( sv->table, col, val, row, handle );
}