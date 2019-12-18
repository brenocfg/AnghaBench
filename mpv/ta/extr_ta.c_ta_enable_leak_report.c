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
struct TYPE_2__ {struct TYPE_2__* leak_next; struct TYPE_2__* leak_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int enable_leak_check ; 
 TYPE_1__ leak_node ; 
 int /*<<< orphan*/  print_leak_report ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ta_dbg_mutex ; 

void ta_enable_leak_report(void)
{
    pthread_mutex_lock(&ta_dbg_mutex);
    enable_leak_check = true;
    if (!leak_node.leak_prev && !leak_node.leak_next) {
        leak_node.leak_prev = &leak_node;
        leak_node.leak_next = &leak_node;
        atexit(print_leak_report);
    }
    pthread_mutex_unlock(&ta_dbg_mutex);
}