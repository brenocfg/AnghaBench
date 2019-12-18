#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {TYPE_1__* ops; } ;
struct TYPE_8__ {int hold; scalar_t__ colinfo; TYPE_3__* table; } ;
struct TYPE_7__ {scalar_t__ (* release ) (TYPE_3__*) ;int /*<<< orphan*/  (* add_ref ) (TYPE_3__*) ;} ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_2__ MSIALTERVIEW ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ alter_add_column (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 scalar_t__ stub2 (TYPE_3__*) ; 

__attribute__((used)) static UINT ALTER_execute( struct tagMSIVIEW *view, MSIRECORD *record )
{
    MSIALTERVIEW *av = (MSIALTERVIEW*)view;
    UINT ref;

    TRACE("%p %p\n", av, record);

    if (av->hold == 1)
        av->table->ops->add_ref(av->table);
    else if (av->hold == -1)
    {
        ref = av->table->ops->release(av->table);
        if (ref == 0)
            av->table = NULL;
    }

    if (av->colinfo)
        return alter_add_column(av);

    return ERROR_SUCCESS;
}