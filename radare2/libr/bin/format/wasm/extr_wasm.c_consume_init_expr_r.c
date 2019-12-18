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
typedef  scalar_t__ ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__ r_buf_read8 (int /*<<< orphan*/ *) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ *) ; 
 scalar_t__ r_buf_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t consume_init_expr_r (RBuffer *b, ut64 max, ut8 eoc, void *out) {
	if (!b || max >= r_buf_size (b) || r_buf_tell (b) > max) {
		return 0;
	}
	size_t res = 0;
	ut8 cur = r_buf_read8 (b);
	while (r_buf_tell (b) <= max && cur != eoc) {
		cur = r_buf_read8 (b);
		res++;
	}
	if (cur != eoc) {
		return 0;
	}
	return res + 1;
}