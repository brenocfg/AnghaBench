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
struct TYPE_2__ {int knownFailureCode; } ;
typedef  TYPE_1__ ws_info ;
struct espconn {scalar_t__ reverse; } ;
typedef  scalar_t__ sint8 ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,scalar_t__) ; 
 int /*<<< orphan*/  disconnect_callback (void*) ; 

__attribute__((used)) static void error_callback(void * arg, sint8 errType) {
  NODE_DBG("error_callback %d\n", errType);
  struct espconn *conn = (struct espconn *) arg;
  ws_info *ws = (ws_info *) conn->reverse;

  ws->knownFailureCode = ((int) errType) - 100;
  disconnect_callback(arg);
}