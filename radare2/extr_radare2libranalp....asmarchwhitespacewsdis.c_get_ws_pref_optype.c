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
typedef  int ut8 ;

/* Variables and functions */
 int WS_OP_FLOW ; 
 int WS_OP_NOP ; 
 int WS_OP_PREF ; 
 int WS_OP_STACK ; 
 int WS_OP_UNK ; 

__attribute__((used)) static int get_ws_pref_optype(const ut8 *buf, int len) {
	if (len < 1) {
		return WS_OP_UNK;
	}
	switch (buf[0]) {
	case ' ': return WS_OP_STACK;
	case '\t': return WS_OP_PREF;
	case 10: return WS_OP_FLOW;
	default: return WS_OP_NOP;
	}
}