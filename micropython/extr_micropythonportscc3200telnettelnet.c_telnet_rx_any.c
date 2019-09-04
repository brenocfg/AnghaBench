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
struct TYPE_2__ {scalar_t__ n_sd; scalar_t__ rxRindex; scalar_t__ rxWindex; scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ E_TELNET_STE_LOGGED_IN ; 
 TYPE_1__ telnet_data ; 

bool telnet_rx_any (void) {
    return (telnet_data.n_sd > 0) ? (telnet_data.rxRindex != telnet_data.rxWindex &&
            telnet_data.state == E_TELNET_STE_LOGGED_IN) : false;
}