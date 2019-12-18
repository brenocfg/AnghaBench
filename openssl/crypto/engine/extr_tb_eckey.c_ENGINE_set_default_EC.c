#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ec_meth; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  dh_table ; 
 int /*<<< orphan*/  dummy_nid ; 
 int engine_table_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  engine_unregister_all_EC ; 

int ENGINE_set_default_EC(ENGINE *e)
{
    if (e->ec_meth != NULL)
        return engine_table_register(&dh_table,
                                     engine_unregister_all_EC, e, &dummy_nid,
                                     1, 1);
    return 1;
}