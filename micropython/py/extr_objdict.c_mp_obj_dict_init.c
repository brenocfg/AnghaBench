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
struct TYPE_4__ {int /*<<< orphan*/ * type; } ;
struct TYPE_5__ {int /*<<< orphan*/  map; TYPE_1__ base; } ;
typedef  TYPE_2__ mp_obj_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_map_init (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mp_type_dict ; 

void mp_obj_dict_init(mp_obj_dict_t *dict, size_t n_args) {
    dict->base.type = &mp_type_dict;
    mp_map_init(&dict->map, n_args);
}