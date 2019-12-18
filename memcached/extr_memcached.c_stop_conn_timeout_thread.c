#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  conn_timeout_tid ; 
 scalar_t__ do_run_conn_timeout_thread ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int stop_conn_timeout_thread(void) {
    if (!do_run_conn_timeout_thread)
        return -1;
    do_run_conn_timeout_thread = 0;
    pthread_join(conn_timeout_tid, NULL);
    return 0;
}