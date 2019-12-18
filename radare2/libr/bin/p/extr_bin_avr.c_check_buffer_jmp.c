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
 int /*<<< orphan*/  CHECK4INSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jmp ; 
 int jmp_dest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 
 int tmp_entry ; 

__attribute__((used)) static bool check_buffer_jmp(RBuffer *b) {
	CHECK4INSTR (b, jmp, 4);
	ut64 dst = jmp_dest (b, 0);
	if (dst < 1 || dst > r_buf_size (b)) {
		return false;
	}
	tmp_entry = dst;
	return true;
}