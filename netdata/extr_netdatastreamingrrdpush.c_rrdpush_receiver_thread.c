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
struct rrdpush_thread {int /*<<< orphan*/  client_port; int /*<<< orphan*/  client_ip; int /*<<< orphan*/  update_every; int /*<<< orphan*/  program_version; int /*<<< orphan*/  program_name; int /*<<< orphan*/  tags; int /*<<< orphan*/  timezone; int /*<<< orphan*/  os; int /*<<< orphan*/  machine_guid; int /*<<< orphan*/  registry_hostname; int /*<<< orphan*/  hostname; int /*<<< orphan*/  key; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettid () ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_pop (int) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  rrdpush_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdpush_receiver_thread_cleanup ; 

__attribute__((used)) static void *rrdpush_receiver_thread(void *ptr) {
    netdata_thread_cleanup_push(rrdpush_receiver_thread_cleanup, ptr);

    struct rrdpush_thread *rpt = (struct rrdpush_thread *)ptr;
    info("STREAM %s [%s]:%s: receive thread created (task id %d)", rpt->hostname, rpt->client_ip, rpt->client_port, gettid());

    rrdpush_receive(
	    rpt->fd
	    , rpt->key
	    , rpt->hostname
	    , rpt->registry_hostname
	    , rpt->machine_guid
	    , rpt->os
	    , rpt->timezone
	    , rpt->tags
	    , rpt->program_name
	    , rpt->program_version
	    , rpt->update_every
	    , rpt->client_ip
	    , rpt->client_port
    );

    netdata_thread_cleanup_pop(1);
    return NULL;
}