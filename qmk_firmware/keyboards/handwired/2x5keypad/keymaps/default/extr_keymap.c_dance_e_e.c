#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  FR_E_HAT ; 
 int /*<<< orphan*/  FR_E_UMLAUT ; 
 int /*<<< orphan*/  send_french_unicode_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dance_e_e(qk_tap_dance_state_t *state, void *user_data)
{
    send_french_unicode_char(state->count, FR_E_HAT, FR_E_UMLAUT);
}