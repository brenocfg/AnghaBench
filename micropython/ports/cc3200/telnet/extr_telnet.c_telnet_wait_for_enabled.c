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
struct TYPE_2__ {int n_sd; int sd; int /*<<< orphan*/  state; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_TELNET_STE_START ; 
 TYPE_1__ telnet_data ; 

__attribute__((used)) static void telnet_wait_for_enabled (void) {
    // Init telnet's data
    telnet_data.n_sd = -1;
    telnet_data.sd   = -1;

    // Check if the telnet service has been enabled
    if (telnet_data.enabled) {
        telnet_data.state = E_TELNET_STE_START;
    }
}