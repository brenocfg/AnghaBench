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
struct TYPE_3__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ ws_info ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  ws_sendFrame (int /*<<< orphan*/ ,int,char const*,unsigned short) ; 

void ws_send(ws_info *ws, int opCode, const char *message, unsigned short length) {
  NODE_DBG("ws_send\n");
  ws_sendFrame(ws->conn, opCode, message, length);
}