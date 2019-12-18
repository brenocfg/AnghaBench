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
typedef  int ut64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK3INSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rjmp ; 
 int rjmp_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tmp_entry ; 

__attribute__((used)) static bool check_buffer_rjmp(RBuffer *b) {
	CHECK3INSTR (b, rjmp, 4);
	ut64 dst = rjmp_dest (0, b);
	if (dst < 1 || dst > r_buf_size (b)) {
		return false;
	}
	tmp_entry = dst;
	return true;
}