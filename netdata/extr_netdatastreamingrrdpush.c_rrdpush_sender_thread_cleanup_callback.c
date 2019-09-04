#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* rrdpush_sender_pipe; int /*<<< orphan*/  hostname; scalar_t__ rrdpush_sender_spawn; int /*<<< orphan*/  rrdpush_sender_join; int /*<<< orphan*/ * rrdpush_sender_buffer; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 size_t PIPE_READ ; 
 size_t PIPE_WRITE ; 
 int /*<<< orphan*/  buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdata_thread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdata_thread_self () ; 
 int /*<<< orphan*/  rrdhost_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdhost_wrlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_buffer_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_buffer_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_sender_thread_close_socket (TYPE_1__*) ; 

__attribute__((used)) static void rrdpush_sender_thread_cleanup_callback(void *ptr) {
    RRDHOST *host = (RRDHOST *)ptr;

    rrdpush_buffer_lock(host);
    rrdhost_wrlock(host);

    info("STREAM %s [send]: sending thread cleans up...", host->hostname);

    rrdpush_sender_thread_close_socket(host);

    // close the pipe
    if(host->rrdpush_sender_pipe[PIPE_READ] != -1) {
        close(host->rrdpush_sender_pipe[PIPE_READ]);
        host->rrdpush_sender_pipe[PIPE_READ] = -1;
    }

    if(host->rrdpush_sender_pipe[PIPE_WRITE] != -1) {
        close(host->rrdpush_sender_pipe[PIPE_WRITE]);
        host->rrdpush_sender_pipe[PIPE_WRITE] = -1;
    }

    buffer_free(host->rrdpush_sender_buffer);
    host->rrdpush_sender_buffer = NULL;

    if(!host->rrdpush_sender_join) {
        info("STREAM %s [send]: sending thread detaches itself.", host->hostname);
        netdata_thread_detach(netdata_thread_self());
    }

    host->rrdpush_sender_spawn = 0;

    info("STREAM %s [send]: sending thread now exits.", host->hostname);

    rrdhost_unlock(host);
    rrdpush_buffer_unlock(host);
}