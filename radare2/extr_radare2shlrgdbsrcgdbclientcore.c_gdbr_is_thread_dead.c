#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_id ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_7__ {int /*<<< orphan*/  multiprocess; } ;
struct TYPE_8__ {int data_len; char* data; TYPE_1__ stub_features; } ;
typedef  TYPE_2__ libgdbr_t ;

/* Variables and functions */
 scalar_t__ read_packet (TYPE_2__*,int) ; 
 scalar_t__ send_ack (TYPE_2__*) ; 
 scalar_t__ send_msg (TYPE_2__*,char*) ; 
 scalar_t__ snprintf (char*,int,char*,char*) ; 
 scalar_t__ write_thread_id (char*,int,int,int,int /*<<< orphan*/ ) ; 

bool gdbr_is_thread_dead (libgdbr_t *g, int pid, int tid) {
	if (!g) {
		return false;
	}
	if (g->stub_features.multiprocess && pid <= 0) {
		return false;
	}
	char msg[64] = { 0 }, thread_id[63] = { 0 };
	if (write_thread_id (thread_id, sizeof (thread_id) - 1, pid, tid,
			     g->stub_features.multiprocess) < 0) {
		return false;
	}
	if (snprintf (msg, sizeof (msg) - 1, "T%s", thread_id) < 0) {
		return false;
	}
	if (send_msg (g, msg) < 0 || read_packet (g, false) < 0 || send_ack (g) < 0) {
		return false;
	}
	if (g->data_len == 3 && g->data[0] == 'E') {
		return true;
	}
	return false;
}