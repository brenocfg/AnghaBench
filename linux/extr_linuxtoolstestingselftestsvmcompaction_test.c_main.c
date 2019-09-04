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
struct rlimit {void* rlim_max; void* rlim_cur; } ;
struct map_list {void* map; struct map_list* next; } ;

/* Variables and functions */
 int KSFT_SKIP ; 
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_LOCKED ; 
 int MAP_PRIVATE ; 
 size_t MAP_SIZE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 void* RLIM_INFINITY ; 
 scalar_t__ check_compaction (unsigned long,unsigned long) ; 
 size_t getpagesize () ; 
 struct map_list* malloc (int) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ prereq () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ read_memory_info (unsigned long*,unsigned long*) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

int main(int argc, char **argv)
{
	struct rlimit lim;
	struct map_list *list, *entry;
	size_t page_size, i;
	void *map = NULL;
	unsigned long mem_free = 0;
	unsigned long hugepage_size = 0;
	unsigned long mem_fragmentable = 0;

	if (prereq() != 0) {
		printf("Either the sysctl compact_unevictable_allowed is not\n"
		       "set to 1 or couldn't read the proc file.\n"
		       "Skipping the test\n");
		return KSFT_SKIP;
	}

	lim.rlim_cur = RLIM_INFINITY;
	lim.rlim_max = RLIM_INFINITY;
	if (setrlimit(RLIMIT_MEMLOCK, &lim)) {
		perror("Failed to set rlimit:\n");
		return -1;
	}

	page_size = getpagesize();

	list = NULL;

	if (read_memory_info(&mem_free, &hugepage_size) != 0) {
		printf("ERROR: Cannot read meminfo\n");
		return -1;
	}

	mem_fragmentable = mem_free * 0.8 / 1024;

	while (mem_fragmentable > 0) {
		map = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE,
			   MAP_ANONYMOUS | MAP_PRIVATE | MAP_LOCKED, -1, 0);
		if (map == MAP_FAILED)
			break;

		entry = malloc(sizeof(struct map_list));
		if (!entry) {
			munmap(map, MAP_SIZE);
			break;
		}
		entry->map = map;
		entry->next = list;
		list = entry;

		/* Write something (in this case the address of the map) to
		 * ensure that KSM can't merge the mapped pages
		 */
		for (i = 0; i < MAP_SIZE; i += page_size)
			*(unsigned long *)(map + i) = (unsigned long)map + i;

		mem_fragmentable--;
	}

	for (entry = list; entry != NULL; entry = entry->next) {
		munmap(entry->map, MAP_SIZE);
		if (!entry->next)
			break;
		entry = entry->next;
	}

	if (check_compaction(mem_free, hugepage_size) == 0)
		return 0;

	return -1;
}