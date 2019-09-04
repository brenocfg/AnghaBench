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
struct plugind {int /*<<< orphan*/  thread; int /*<<< orphan*/  id; int /*<<< orphan*/  obsolete; scalar_t__ enabled; struct plugind* next; } ;
struct netdata_static_thread {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDATA_MAIN_THREAD_EXITED ; 
 int /*<<< orphan*/  NETDATA_MAIN_THREAD_EXITING ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  netdata_thread_cancel (int /*<<< orphan*/ ) ; 
 struct plugind* pluginsd_root ; 

__attribute__((used)) static void pluginsd_main_cleanup(void *data) {
    struct netdata_static_thread *static_thread = (struct netdata_static_thread *)data;
    static_thread->enabled = NETDATA_MAIN_THREAD_EXITING;
    info("cleaning up...");

    struct plugind *cd;
    for (cd = pluginsd_root; cd; cd = cd->next) {
        if (cd->enabled && !cd->obsolete) {
            info("stopping plugin thread: %s", cd->id);
            netdata_thread_cancel(cd->thread);
        }
    }

    info("cleanup completed.");
    static_thread->enabled = NETDATA_MAIN_THREAD_EXITED;
}