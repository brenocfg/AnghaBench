#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qstr ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_4__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  TYPE_2__ mp_obj_super_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_2__*) ; 
 int /*<<< orphan*/  mp_load_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_super ; 

void mp_load_super_method(qstr attr, mp_obj_t *dest) {
    mp_obj_super_t super = {{&mp_type_super}, dest[1], dest[2]};
    mp_load_method(MP_OBJ_FROM_PTR(&super), attr, dest);
}