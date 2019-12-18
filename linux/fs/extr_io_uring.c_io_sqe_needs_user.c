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
typedef  scalar_t__ u8 ;
struct io_uring_sqe {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 scalar_t__ IORING_OP_READ_FIXED ; 
 scalar_t__ IORING_OP_WRITE_FIXED ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool io_sqe_needs_user(const struct io_uring_sqe *sqe)
{
	u8 opcode = READ_ONCE(sqe->opcode);

	return !(opcode == IORING_OP_READ_FIXED ||
		 opcode == IORING_OP_WRITE_FIXED);
}