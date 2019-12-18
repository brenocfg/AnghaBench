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
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  mfd_def_size ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void *mfd_assert_mmap_private(int fd)
{
	void *p;

	p = mmap(NULL,
		 mfd_def_size,
		 PROT_READ | PROT_WRITE,
		 MAP_PRIVATE,
		 fd,
		 0);
	if (p == MAP_FAILED) {
		printf("mmap() failed: %m\n");
		abort();
	}

	return p;
}