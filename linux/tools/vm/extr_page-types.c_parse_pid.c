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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 size_t MAX_VMAS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  checked_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t nr_vmas ; 
 int opt_pid ; 
 unsigned long page_size ; 
 int /*<<< orphan*/  pagemap_fd ; 
 int parse_number (char const*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 unsigned long* pg_end ; 
 unsigned long* pg_start ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int sscanf (char*,char*,unsigned long*,unsigned long*,char*,char*,char*,char*,unsigned long long*,int*,int*,unsigned long*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void parse_pid(const char *str)
{
	FILE *file;
	char buf[5000];

	opt_pid = parse_number(str);

	sprintf(buf, "/proc/%d/pagemap", opt_pid);
	pagemap_fd = checked_open(buf, O_RDONLY);

	sprintf(buf, "/proc/%d/maps", opt_pid);
	file = fopen(buf, "r");
	if (!file) {
		perror(buf);
		exit(EXIT_FAILURE);
	}

	while (fgets(buf, sizeof(buf), file) != NULL) {
		unsigned long vm_start;
		unsigned long vm_end;
		unsigned long long pgoff;
		int major, minor;
		char r, w, x, s;
		unsigned long ino;
		int n;

		n = sscanf(buf, "%lx-%lx %c%c%c%c %llx %x:%x %lu",
			   &vm_start,
			   &vm_end,
			   &r, &w, &x, &s,
			   &pgoff,
			   &major, &minor,
			   &ino);
		if (n < 10) {
			fprintf(stderr, "unexpected line: %s\n", buf);
			continue;
		}
		pg_start[nr_vmas] = vm_start / page_size;
		pg_end[nr_vmas] = vm_end / page_size;
		if (++nr_vmas >= MAX_VMAS) {
			fprintf(stderr, "too many VMAs\n");
			break;
		}
	}
	fclose(file);
}