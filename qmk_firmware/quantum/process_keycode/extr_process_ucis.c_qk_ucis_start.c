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
struct TYPE_2__ {int in_progress; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  qk_ucis_start_user () ; 
 TYPE_1__ qk_ucis_state ; 

void qk_ucis_start(void) {
    qk_ucis_state.count       = 0;
    qk_ucis_state.in_progress = true;

    qk_ucis_start_user();
}