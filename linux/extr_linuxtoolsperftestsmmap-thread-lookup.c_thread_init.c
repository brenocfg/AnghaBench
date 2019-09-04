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
struct thread_data {int /*<<< orphan*/  tid; void* map; } ;

/* Variables and functions */
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SYS_gettid ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_size ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thread_init(struct thread_data *td)
{
	void *map;

	map = mmap(NULL, page_size,
		   PROT_READ|PROT_WRITE|PROT_EXEC,
		   MAP_SHARED|MAP_ANONYMOUS, -1, 0);

	if (map == MAP_FAILED) {
		perror("mmap failed");
		return -1;
	}

	td->map = map;
	td->tid = syscall(SYS_gettid);

	pr_debug("tid = %d, map = %p\n", td->tid, map);
	return 0;
}