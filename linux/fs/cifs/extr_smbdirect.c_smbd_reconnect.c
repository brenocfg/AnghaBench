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
struct sockaddr {int dummy; } ;
struct TCP_Server_Info {TYPE_1__* smbd_conn; int /*<<< orphan*/  dstaddr; } ;
struct TYPE_2__ {scalar_t__ transport_status; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ SMBD_CONNECTED ; 
 int /*<<< orphan*/  log_rdma_event (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  smbd_destroy (struct TCP_Server_Info*) ; 
 TYPE_1__* smbd_get_connection (struct TCP_Server_Info*,struct sockaddr*) ; 

int smbd_reconnect(struct TCP_Server_Info *server)
{
	log_rdma_event(INFO, "reconnecting rdma session\n");

	if (!server->smbd_conn) {
		log_rdma_event(INFO, "rdma session already destroyed\n");
		goto create_conn;
	}

	/*
	 * This is possible if transport is disconnected and we haven't received
	 * notification from RDMA, but upper layer has detected timeout
	 */
	if (server->smbd_conn->transport_status == SMBD_CONNECTED) {
		log_rdma_event(INFO, "disconnecting transport\n");
		smbd_destroy(server);
	}

create_conn:
	log_rdma_event(INFO, "creating rdma session\n");
	server->smbd_conn = smbd_get_connection(
		server, (struct sockaddr *) &server->dstaddr);
	log_rdma_event(INFO, "created rdma session info=%p\n",
		server->smbd_conn);

	return server->smbd_conn ? 0 : -ENOENT;
}