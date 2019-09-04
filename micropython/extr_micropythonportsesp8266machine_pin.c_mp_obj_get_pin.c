#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_2__ {int /*<<< orphan*/  phys_port; } ;

/* Variables and functions */
 TYPE_1__* mp_obj_get_pin_obj (int /*<<< orphan*/ ) ; 

uint mp_obj_get_pin(mp_obj_t pin_in) {
    return mp_obj_get_pin_obj(pin_in)->phys_port;
}