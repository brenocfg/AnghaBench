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
typedef  int /*<<< orphan*/  buf ;
typedef  unsigned int Size ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char*,char*) ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 int MAP_HUGETLB ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,unsigned int*,char*) ; 

__attribute__((used)) static void
GetHugePageSize(Size *hugepagesize, int *mmap_flags)
{
	/*
	 * If we fail to find out the system's default huge page size, assume it
	 * is 2MB.  This will work fine when the actual size is less.  If it's
	 * more, we might get mmap() or munmap() failures due to unaligned
	 * requests; but at this writing, there are no reports of any non-Linux
	 * systems being picky about that.
	 */
	*hugepagesize = 2 * 1024 * 1024;
	*mmap_flags = MAP_HUGETLB;

	/*
	 * System-dependent code to find out the default huge page size.
	 *
	 * On Linux, read /proc/meminfo looking for a line like "Hugepagesize:
	 * nnnn kB".  Ignore any failures, falling back to the preset default.
	 */
#ifdef __linux__
	{
		FILE	   *fp = AllocateFile("/proc/meminfo", "r");
		char		buf[128];
		unsigned int sz;
		char		ch;

		if (fp)
		{
			while (fgets(buf, sizeof(buf), fp))
			{
				if (sscanf(buf, "Hugepagesize: %u %c", &sz, &ch) == 2)
				{
					if (ch == 'k')
					{
						*hugepagesize = sz * (Size) 1024;
						break;
					}
					/* We could accept other units besides kB, if needed */
				}
			}
			FreeFile(fp);
		}
	}
#endif							/* __linux__ */
}