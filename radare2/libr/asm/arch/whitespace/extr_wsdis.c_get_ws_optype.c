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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 scalar_t__ WS_OP_NOP ; 
 scalar_t__ WS_OP_PREF ; 
 int get_ws_pref_optype (int /*<<< orphan*/  const*,int) ; 
 int get_ws_suf_optype (int /*<<< orphan*/  const*,int) ; 

int get_ws_optype(const ut8 *buf, int len) {
	const ut8 *ptr;
	if (get_ws_pref_optype (buf, len) == WS_OP_PREF) {
		ptr = buf + 1;
		while (get_ws_suf_optype (ptr, len - (ptr - buf)) == WS_OP_NOP) {
			ptr++;
		}
		return get_ws_suf_optype (ptr, len - (ptr - buf));
	}
	return get_ws_pref_optype (buf, len);
}