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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAPS_LINE_LEN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int sscanf (char*,char*,void**,void**,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void *vsyscall_getcpu(void)
{
#ifdef __x86_64__
	FILE *maps;
	char line[MAPS_LINE_LEN];
	bool found = false;

	maps = fopen("/proc/self/maps", "r");
	if (!maps) /* might still be present, but ignore it here, as we test vDSO not vsyscall */
		return NULL;

	while (fgets(line, MAPS_LINE_LEN, maps)) {
		char r, x;
		void *start, *end;
		char name[MAPS_LINE_LEN];

		/* sscanf() is safe here as strlen(name) >= strlen(line) */
		if (sscanf(line, "%p-%p %c-%cp %*x %*x:%*x %*u %s",
			   &start, &end, &r, &x, name) != 5)
			continue;

		if (strcmp(name, "[vsyscall]"))
			continue;

		/* assume entries are OK, as we test vDSO here not vsyscall */
		found = true;
		break;
	}

	fclose(maps);

	if (!found) {
		printf("Warning: failed to find vsyscall getcpu\n");
		return NULL;
	}
	return (void *) (0xffffffffff600800);
#else
	return NULL;
#endif
}