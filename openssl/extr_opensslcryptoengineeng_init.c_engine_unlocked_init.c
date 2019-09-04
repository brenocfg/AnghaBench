#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ funct_ref; int (* init ) (TYPE_1__*) ;int /*<<< orphan*/  struct_ref; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  engine_ref_debug (TYPE_1__*,int,int) ; 
 int stub1 (TYPE_1__*) ; 

int engine_unlocked_init(ENGINE *e)
{
    int to_return = 1;

    if ((e->funct_ref == 0) && e->init)
        /*
         * This is the first functional reference and the engine requires
         * initialisation so we do it now.
         */
        to_return = e->init(e);
    if (to_return) {
        /*
         * OK, we return a functional reference which is also a structural
         * reference.
         */
        e->struct_ref++;
        e->funct_ref++;
        engine_ref_debug(e, 0, 1);
        engine_ref_debug(e, 1, 1);
    }
    return to_return;
}