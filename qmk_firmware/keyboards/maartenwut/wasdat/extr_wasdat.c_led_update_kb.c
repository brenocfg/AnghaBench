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
struct TYPE_4__ {int /*<<< orphan*/  num_lock; int /*<<< orphan*/  scroll_lock; int /*<<< orphan*/  caps_lock; } ;
typedef  TYPE_1__ led_t ;

/* Variables and functions */
 int /*<<< orphan*/  B0 ; 
 int /*<<< orphan*/  B1 ; 
 int /*<<< orphan*/  B2 ; 
 scalar_t__ led_update_user (TYPE_1__) ; 
 int /*<<< orphan*/  writePin (int /*<<< orphan*/ ,int) ; 

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B0, !led_state.caps_lock);
        writePin(B1, !led_state.scroll_lock);
        writePin(B2, !led_state.num_lock);
    }

    return true;
}