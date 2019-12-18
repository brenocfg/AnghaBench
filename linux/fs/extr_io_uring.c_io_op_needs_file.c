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
struct io_uring_sqe {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
#define  IORING_OP_NOP 129 
#define  IORING_OP_POLL_REMOVE 128 
 int READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool io_op_needs_file(const struct io_uring_sqe *sqe)
{
	int op = READ_ONCE(sqe->opcode);

	switch (op) {
	case IORING_OP_NOP:
	case IORING_OP_POLL_REMOVE:
		return false;
	default:
		return true;
	}
}