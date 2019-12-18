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
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int check_buffer_jmp (int /*<<< orphan*/ *) ; 
 int check_buffer_rjmp (int /*<<< orphan*/ *) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rjmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_buffer(RBuffer *buf) {
	if (r_buf_size (buf) < 32) {
		return false;
	}
	if (!rjmp (buf, 0)) {
		return check_buffer_jmp (buf);
	}
	return check_buffer_rjmp (buf);
}