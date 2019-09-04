#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int connectionState; int /*<<< orphan*/  timeoutTimer; int /*<<< orphan*/  conn; scalar_t__ knownFailureCode; } ;
typedef  TYPE_1__ ws_info ;
typedef  int /*<<< orphan*/  os_timer_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  SWTIMER_REG_CB (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWTIMER_RESUME ; 
 int /*<<< orphan*/  WS_FORCE_CLOSE_TIMEOUT_MS ; 
 int /*<<< orphan*/  WS_OPCODE_CLOSE ; 
 int /*<<< orphan*/  disconnect_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ws_forceCloseTimeout ; 
 int /*<<< orphan*/  ws_sendFrame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ws_close(ws_info *ws) {
  NODE_DBG("ws_close\n");

  if (ws->connectionState == 0 || ws->connectionState == 4) {
    return;
  }

  ws->knownFailureCode = 0; // no error as user requested to close
  if (ws->connectionState == 1) {
    disconnect_callback(ws->conn);
  } else {
    ws_sendFrame(ws->conn, WS_OPCODE_CLOSE, NULL, 0);

    os_timer_disarm(&ws->timeoutTimer);
    os_timer_setfn(&ws->timeoutTimer, (os_timer_func_t *) ws_forceCloseTimeout, ws->conn);
    SWTIMER_REG_CB(ws_forceCloseTimeout, SWTIMER_RESUME);
    os_timer_arm(&ws->timeoutTimer, WS_FORCE_CLOSE_TIMEOUT_MS, false);
  }
}