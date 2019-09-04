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
struct TYPE_6__ {int connectionState; int knownFailureCode; int /*<<< orphan*/  (* onFailure ) (TYPE_2__*,int) ;int /*<<< orphan*/ * conn; struct espconn* payloadBuffer; struct espconn* frameBuffer; struct espconn* expectedSecKey; struct espconn* path; struct espconn* hostname; int /*<<< orphan*/  timeoutTimer; } ;
typedef  TYPE_2__ ws_info ;
struct TYPE_5__ {struct espconn* tcp; } ;
struct espconn {TYPE_1__ proto; scalar_t__ reverse; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int /*<<< orphan*/  espconn_delete (struct espconn*) ; 
 int /*<<< orphan*/  os_free (struct espconn*) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 

__attribute__((used)) static void disconnect_callback(void *arg) {
  NODE_DBG("disconnect_callback\n");
  struct espconn *conn = (struct espconn *) arg;
  ws_info *ws = (ws_info *) conn->reverse;

  ws->connectionState = 4;

  os_timer_disarm(&ws->timeoutTimer);

  NODE_DBG("ws->hostname %d\n", ws->hostname);
  os_free(ws->hostname);
  NODE_DBG("ws->path %d\n ", ws->path);
  os_free(ws->path);

  if (ws->expectedSecKey != NULL) {
    os_free(ws->expectedSecKey);
  }

  if (ws->frameBuffer != NULL) {
    os_free(ws->frameBuffer);
  }

  if (ws->payloadBuffer != NULL) {
    os_free(ws->payloadBuffer);
  }

  if (conn->proto.tcp != NULL) {
    os_free(conn->proto.tcp);
  }

  NODE_DBG("conn %d\n", conn);
  espconn_delete(conn);

  NODE_DBG("freeing conn1 \n");

  os_free(conn);
  ws->conn = NULL;

  if (ws->onFailure) {
    if (ws->knownFailureCode) ws->onFailure(ws, ws->knownFailureCode);
    else ws->onFailure(ws, -99);
  }
}