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
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;
struct r_bin_wasm_resizable_limits_t {int /*<<< orphan*/  maximum; scalar_t__ flags; int /*<<< orphan*/  initial; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  R_ABS (scalar_t__) ; 
 int /*<<< orphan*/  consume_u32_r (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  consume_u7_r (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ *) ; 
 scalar_t__ r_buf_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t consume_limits_r (RBuffer *b, ut64 max, struct r_bin_wasm_resizable_limits_t *out) {
	if (!b || max >= r_buf_size (b) || r_buf_tell (b) > max || !out) {
		return 0;
	}
	ut32 i = r_buf_tell (b);
	if (!(consume_u7_r (b, max, &out->flags))) {
		return 0;
	}
	if (!(consume_u32_r (b, max, &out->initial))) {
		return 0;
	}
	if (out->flags && (!(consume_u32_r (b, max, &out->maximum)))) {
		return 0;
	}
	return (size_t)R_ABS (r_buf_tell (b) - i);
}