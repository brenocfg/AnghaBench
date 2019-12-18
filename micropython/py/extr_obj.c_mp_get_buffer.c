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
typedef  int /*<<< orphan*/  mp_uint_t ;
struct TYPE_4__ {int (* get_buffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ buffer_p; } ;
typedef  TYPE_2__ mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_buffer_info_t ;

/* Variables and functions */
 TYPE_2__* mp_obj_get_type (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool mp_get_buffer(mp_obj_t obj, mp_buffer_info_t *bufinfo, mp_uint_t flags) {
    mp_obj_type_t *type = mp_obj_get_type(obj);
    if (type->buffer_p.get_buffer == NULL) {
        return false;
    }
    int ret = type->buffer_p.get_buffer(obj, bufinfo, flags);
    if (ret != 0) {
        return false;
    }
    return true;
}