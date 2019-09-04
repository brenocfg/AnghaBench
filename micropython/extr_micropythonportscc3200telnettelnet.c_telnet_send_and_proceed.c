#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  telnet_connected_substate_t ;
typedef  int /*<<< orphan*/  _i16 ;
struct TYPE_3__ {int /*<<< orphan*/  connected; } ;
struct TYPE_4__ {TYPE_1__ substate; } ;

/* Variables and functions */
 scalar_t__ E_TELNET_RESULT_OK ; 
 TYPE_2__ telnet_data ; 
 scalar_t__ telnet_send_non_blocking (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void telnet_send_and_proceed (void *data, _i16 Len, telnet_connected_substate_t next_state) {
    if (E_TELNET_RESULT_OK == telnet_send_non_blocking(data, Len)) {
        telnet_data.substate.connected = next_state;
    }
}