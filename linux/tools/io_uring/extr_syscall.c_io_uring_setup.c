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
struct io_uring_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_io_uring_setup ; 
 int syscall (int /*<<< orphan*/ ,unsigned int,struct io_uring_params*) ; 

int io_uring_setup(unsigned int entries, struct io_uring_params *p)
{
	return syscall(__NR_io_uring_setup, entries, p);
}