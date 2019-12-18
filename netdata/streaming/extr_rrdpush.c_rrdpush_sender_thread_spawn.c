#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rrdpush_sender_spawn; int /*<<< orphan*/  hostname; int /*<<< orphan*/  rrdpush_sender_thread; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  NETDATA_THREAD_OPTION_JOINABLE ; 
 int /*<<< orphan*/  NETDATA_THREAD_TAG_MAX ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ netdata_thread_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  rrdhost_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdhost_wrlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_sender_thread ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rrdpush_sender_thread_spawn(RRDHOST *host) {
    rrdhost_wrlock(host);

    if(!host->rrdpush_sender_spawn) {
        char tag[NETDATA_THREAD_TAG_MAX + 1];
        snprintfz(tag, NETDATA_THREAD_TAG_MAX, "STREAM_SENDER[%s]", host->hostname);

        if(netdata_thread_create(&host->rrdpush_sender_thread, tag, NETDATA_THREAD_OPTION_JOINABLE, rrdpush_sender_thread, (void *) host))
            error("STREAM %s [send]: failed to create new thread for client.", host->hostname);
        else
            host->rrdpush_sender_spawn = 1;
    }

    rrdhost_unlock(host);
}