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

/* Variables and functions */
 int /*<<< orphan*/  BPF_SOCKHASH_FILENAME ; 
 int /*<<< orphan*/  BPF_SOCKMAP_FILENAME ; 
 int __test_suite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static int test_suite(int cg_fd)
{
	int err;

	err = __test_suite(cg_fd, BPF_SOCKMAP_FILENAME);
	if (err)
		goto out;
	err = __test_suite(cg_fd, BPF_SOCKHASH_FILENAME);
out:
	if (cg_fd > -1)
		close(cg_fd);
	return err;
}