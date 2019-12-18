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
struct plugind {char* pid; int /*<<< orphan*/  enabled; int /*<<< orphan*/  fullfilename; int /*<<< orphan*/  cmd; scalar_t__ obsolete; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  killpid (char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  localhost ; 
 int mypclose (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * mypopen (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  netdata_exit ; 
 int /*<<< orphan*/  netdata_thread_cleanup_pop (int) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 size_t pluginsd_process (int /*<<< orphan*/ ,struct plugind*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluginsd_worker_thread_cleanup ; 
 int /*<<< orphan*/  pluginsd_worker_thread_handle_error (struct plugind*,int) ; 
 int /*<<< orphan*/  pluginsd_worker_thread_handle_success (struct plugind*) ; 
 scalar_t__ unlikely (int) ; 

void *pluginsd_worker_thread(void *arg) {
    netdata_thread_cleanup_push(pluginsd_worker_thread_cleanup, arg);

    struct plugind *cd = (struct plugind *)arg;

    cd->obsolete = 0;
    size_t count = 0;

    while(!netdata_exit) {
        FILE *fp = mypopen(cd->cmd, &cd->pid);
        if(unlikely(!fp)) {
            error("Cannot popen(\"%s\", \"r\").", cd->cmd);
            break;
        }

        info("connected to '%s' running on pid %d", cd->fullfilename, cd->pid);
        count = pluginsd_process(localhost, cd, fp, 0);
        error("'%s' (pid %d) disconnected after %zu successful data collections (ENDs).", cd->fullfilename, cd->pid, count);
        killpid(cd->pid);

        int worker_ret_code = mypclose(fp, cd->pid);

        if (likely(worker_ret_code == 0))
            pluginsd_worker_thread_handle_success(cd);
        else
            pluginsd_worker_thread_handle_error(cd, worker_ret_code);

        cd->pid = 0;
        if(unlikely(!cd->enabled)) break;
    }

    netdata_thread_cleanup_pop(1);
    return NULL;
}