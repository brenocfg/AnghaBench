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
typedef  scalar_t__ const ut8 ;

/* Variables and functions */
 scalar_t__* get_ws_next_token (scalar_t__ const*,int) ; 

int test_ws_token_exist(const ut8 *buf, ut8 token, int len) {
	const ut8 *ptr = get_ws_next_token (buf, len);
	int size = 1;
	while (ptr && *ptr != token && (len > 0)) {
		len = len - (ptr - buf);
		ptr = get_ws_next_token (ptr + 1, len - 1);
		size++;
	}
	return size;
}