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
struct testcase {char* msg; int /*<<< orphan*/  size; int /*<<< orphan*/  keep_mapped; scalar_t__ low_addr_required; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ ADDR_SWITCH_HINT ; 
 void* MAP_FAILED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int run_test(struct testcase *test, int count)
{
	void *p;
	int i, ret = 0;

	for (i = 0; i < count; i++) {
		struct testcase *t = test + i;

		p = mmap(t->addr, t->size, PROT_READ | PROT_WRITE, t->flags, -1, 0);

		printf("%s: %p - ", t->msg, p);

		if (p == MAP_FAILED) {
			printf("FAILED\n");
			ret = 1;
			continue;
		}

		if (t->low_addr_required && p >= (void *)(ADDR_SWITCH_HINT)) {
			printf("FAILED\n");
			ret = 1;
		} else {
			/*
			 * Do a dereference of the address returned so that we catch
			 * bugs in page fault handling
			 */
			memset(p, 0, t->size);
			printf("OK\n");
		}
		if (!t->keep_mapped)
			munmap(p, t->size);
	}

	return ret;
}