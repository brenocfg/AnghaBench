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
struct TYPE_3__ {int /*<<< orphan*/  abort; } ;
typedef  TYPE_1__ dwc_thread_t ;
typedef  int /*<<< orphan*/  dwc_bool_t ;

/* Variables and functions */

dwc_bool_t DWC_THREAD_SHOULD_STOP(dwc_thread_t *thread)
{
	return thread->abort;
}