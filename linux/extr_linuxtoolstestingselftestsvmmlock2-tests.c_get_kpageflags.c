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
typedef  int /*<<< orphan*/  flags ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static uint64_t get_kpageflags(unsigned long pfn)
{
	uint64_t flags;
	FILE *file;

	file = fopen("/proc/kpageflags", "r");
	if (!file) {
		perror("fopen kpageflags");
		_exit(1);
	}

	if (fseek(file, pfn * sizeof(flags), SEEK_SET)) {
		perror("fseek kpageflags");
		_exit(1);
	}

	if (fread(&flags, sizeof(flags), 1, file) != 1) {
		perror("fread kpageflags");
		_exit(1);
	}

	fclose(file);
	return flags;
}