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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_consumer ) (scalar_t__) ;} ;

/* Variables and functions */
 TYPE_1__* driver ; 
 scalar_t__ last_consumer_report ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void host_consumer_send(uint16_t report) {
    if (report == last_consumer_report) return;
    last_consumer_report = report;

    if (!driver) return;
    (*driver->send_consumer)(report);
}