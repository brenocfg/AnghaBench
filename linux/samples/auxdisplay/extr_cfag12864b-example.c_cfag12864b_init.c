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
 int /*<<< orphan*/  CFAG12864B_SIZE ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int cfag12864b_fd ; 
 scalar_t__ cfag12864b_mem ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfag12864b_init(char *path)
{
	cfag12864b_fd = open(path, O_RDWR);
	if (cfag12864b_fd == -1)
		return -1;

	cfag12864b_mem = mmap(0, CFAG12864B_SIZE, PROT_READ | PROT_WRITE,
		MAP_SHARED, cfag12864b_fd, 0);
	if (cfag12864b_mem == MAP_FAILED) {
		close(cfag12864b_fd);
		return -2;
	}

	return 0;
}