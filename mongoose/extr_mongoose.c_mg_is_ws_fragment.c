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
 unsigned char FLAGS_MASK_FIN ; 
 unsigned char FLAGS_MASK_OP ; 
 unsigned char WEBSOCKET_OP_CONTINUE ; 

__attribute__((used)) static int mg_is_ws_fragment(unsigned char flags) {
  return (flags & FLAGS_MASK_FIN) == 0 ||
         (flags & FLAGS_MASK_OP) == WEBSOCKET_OP_CONTINUE;
}