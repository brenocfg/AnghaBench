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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  pfn ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long getpagesize () ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static uint64_t get_pageflags(unsigned long addr)
{
	FILE *file;
	uint64_t pfn;
	unsigned long offset;

	file = fopen("/proc/self/pagemap", "r");
	if (!file) {
		perror("fopen pagemap");
		_exit(1);
	}

	offset = addr / getpagesize() * sizeof(pfn);

	if (fseek(file, offset, SEEK_SET)) {
		perror("fseek pagemap");
		_exit(1);
	}

	if (fread(&pfn, sizeof(pfn), 1, file) != 1) {
		perror("fread pagemap");
		_exit(1);
	}

	fclose(file);
	return pfn;
}