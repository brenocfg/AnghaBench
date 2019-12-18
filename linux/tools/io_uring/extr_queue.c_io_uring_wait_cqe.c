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
struct io_uring_cqe {int dummy; } ;
struct io_uring {int dummy; } ;

/* Variables and functions */
 int __io_uring_get_cqe (struct io_uring*,struct io_uring_cqe**,int) ; 

int io_uring_wait_cqe(struct io_uring *ring, struct io_uring_cqe **cqe_ptr)
{
	return __io_uring_get_cqe(ring, cqe_ptr, 1);
}