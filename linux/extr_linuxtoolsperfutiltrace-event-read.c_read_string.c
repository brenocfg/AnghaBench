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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  input_fd ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ repipe ; 
 int trace_data_size ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *read_string(void)
{
	char buf[BUFSIZ];
	char *str = NULL;
	int size = 0;
	off_t r;
	char c;

	for (;;) {
		r = read(input_fd, &c, 1);
		if (r < 0) {
			pr_debug("reading input file");
			goto out;
		}

		if (!r) {
			pr_debug("no data");
			goto out;
		}

		if (repipe) {
			int retw = write(STDOUT_FILENO, &c, 1);

			if (retw <= 0 || retw != r) {
				pr_debug("repiping input file string");
				goto out;
			}
		}

		buf[size++] = c;

		if (!c)
			break;
	}

	trace_data_size += size;

	str = malloc(size);
	if (str)
		memcpy(str, buf, size);
out:
	return str;
}