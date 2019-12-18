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
struct TYPE_2__ {scalar_t__ idle_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_timeout_thread ; 
 int /*<<< orphan*/  conn_timeout_tid ; 
 int do_run_conn_timeout_thread ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static int start_conn_timeout_thread() {
    int ret;

    if (settings.idle_timeout == 0)
        return -1;

    do_run_conn_timeout_thread = 1;
    if ((ret = pthread_create(&conn_timeout_tid, NULL,
        conn_timeout_thread, NULL)) != 0) {
        fprintf(stderr, "Can't create idle connection timeout thread: %s\n",
            strerror(ret));
        return -1;
    }

    return 0;
}