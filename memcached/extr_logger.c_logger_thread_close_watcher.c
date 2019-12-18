#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t id; int /*<<< orphan*/  buf; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ logger_watcher ;

/* Variables and functions */
 int /*<<< orphan*/  L_DEBUG (char*) ; 
 int /*<<< orphan*/  bipbuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  logger_set_flags () ; 
 int /*<<< orphan*/  sidethread_conn_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watcher_count ; 
 int /*<<< orphan*/ ** watchers ; 

__attribute__((used)) static void logger_thread_close_watcher(logger_watcher *w) {
    L_DEBUG("LOGGER: Closing dead watcher\n");
    watchers[w->id] = NULL;
    sidethread_conn_close(w->c);
    watcher_count--;
    bipbuf_free(w->buf);
    free(w);
    logger_set_flags();
}