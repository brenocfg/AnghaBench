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
struct TYPE_2__ {int knownFailureCode; scalar_t__ isSecure; } ;
typedef  TYPE_1__ ws_info ;
struct espconn {scalar_t__ reverse; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  espconn_disconnect (struct espconn*) ; 
 int /*<<< orphan*/  espconn_secure_disconnect (struct espconn*) ; 

__attribute__((used)) static void ws_closeSentCallback(void *arg) {
  NODE_DBG("ws_closeSentCallback \n");
  struct espconn *conn = (struct espconn *) arg;
  ws_info *ws = (ws_info *) conn->reverse;

  if (ws == NULL) {
    NODE_DBG("ws is unexpectly null\n");
    return;
  }

  ws->knownFailureCode = -6;

  if (ws->isSecure)
    espconn_secure_disconnect(conn);
  else
    espconn_disconnect(conn);
}