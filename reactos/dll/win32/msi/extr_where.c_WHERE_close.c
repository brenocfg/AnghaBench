#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {TYPE_1__* ops; } ;
struct TYPE_8__ {TYPE_4__* view; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_3__* tables; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (TYPE_4__*) ;} ;
typedef  TYPE_2__ MSIWHEREVIEW ;
typedef  TYPE_3__ JOINTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static UINT WHERE_close( struct tagMSIVIEW *view )
{
    MSIWHEREVIEW *wv = (MSIWHEREVIEW*)view;
    JOINTABLE *table = wv->tables;

    TRACE("%p\n", wv );

    if (!table)
        return ERROR_FUNCTION_FAILED;

    do
        table->view->ops->close(table->view);
    while ((table = table->next));

    return ERROR_SUCCESS;
}