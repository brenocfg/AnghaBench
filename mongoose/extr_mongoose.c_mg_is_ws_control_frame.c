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

/* Variables and functions */
 unsigned char FLAGS_MASK_OP ; 
 unsigned char WEBSOCKET_OP_CLOSE ; 
 unsigned char WEBSOCKET_OP_PING ; 
 unsigned char WEBSOCKET_OP_PONG ; 

__attribute__((used)) static int mg_is_ws_control_frame(unsigned char flags) {
  unsigned char op = (flags & FLAGS_MASK_OP);
  return op == WEBSOCKET_OP_CLOSE || op == WEBSOCKET_OP_PING ||
         op == WEBSOCKET_OP_PONG;
}