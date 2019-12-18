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
struct TYPE_7__ {int /*<<< orphan*/  rrdpush_sender_buffer; int /*<<< orphan*/  hostname; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_flush (int /*<<< orphan*/ ) ; 
 char* buffer_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rrdpush_buffer_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_buffer_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_sender_thread_reset_all_charts (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_sender_thread_send_custom_host_variables (TYPE_1__*) ; 

__attribute__((used)) static inline void rrdpush_sender_thread_data_flush(RRDHOST *host) {
    rrdpush_buffer_lock(host);

    if(buffer_strlen(host->rrdpush_sender_buffer))
        error("STREAM %s [send]: discarding %zu bytes of metrics already in the buffer.", host->hostname, buffer_strlen(host->rrdpush_sender_buffer));

    buffer_flush(host->rrdpush_sender_buffer);

    rrdpush_sender_thread_reset_all_charts(host);
    rrdpush_sender_thread_send_custom_host_variables(host);

    rrdpush_buffer_unlock(host);
}