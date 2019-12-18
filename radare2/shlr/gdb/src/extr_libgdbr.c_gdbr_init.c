#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int extended_mode; int pkt_sz; } ;
struct TYPE_6__ {int no_ack; int remote_file_fd; int is_server; int send_max; char* send_buff; int page_size; int num_retries; int read_max; char* read_buff; int data_max; int /*<<< orphan*/  remote_type; scalar_t__ data; scalar_t__ data_len; scalar_t__ connected; int /*<<< orphan*/  last_code; int /*<<< orphan*/  gdbr_lock; int /*<<< orphan*/  sock; scalar_t__ send_len; TYPE_1__ stub_features; } ;
typedef  TYPE_2__ libgdbr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_REMOTE_TYPE_GDB ; 
 int /*<<< orphan*/  MSG_OK ; 
 int /*<<< orphan*/  R_FREE (char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_socket_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_th_lock_new (int) ; 

int gdbr_init(libgdbr_t *g, bool is_server) {
	if (!g) {
		return -1;
	}
	memset (g, 0, sizeof (libgdbr_t));
	g->no_ack = false;
	g->stub_features.extended_mode = -1;
	g->stub_features.pkt_sz = 64;
	g->remote_file_fd = -1;
	g->is_server = is_server;
	g->send_max = 2500;
	g->send_buff = (char *) calloc (g->send_max, 1);
	g->page_size = 4096;
	g->num_retries = 40; // safe number, should be ~10 seconds
	if (!g->send_buff) {
		return -1;
	}
	g->send_len = 0;
	g->read_max = 4096;
	g->read_buff = (char *) calloc (g->read_max, 1);
	if (!g->read_buff) {
		R_FREE (g->send_buff);
		return -1;
	}
	g->sock = r_socket_new (0);
	g->gdbr_lock = r_th_lock_new (true);
	g->last_code = MSG_OK;
	g->connected = 0;
	g->data_len = 0;
	g->data_max = 4096;
	g->data = calloc (g->data_max, 1);
	if (!g->data) {
		R_FREE (g->send_buff);
		R_FREE (g->read_buff);
		return -1;
	}
	g->remote_type = GDB_REMOTE_TYPE_GDB;
	return 0;
}