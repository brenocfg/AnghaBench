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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static void fs_something(void)
{
	const char *test_file_name = "temp-perf-code-reading-test-file--";
	FILE *f;
	int i;

	for (i = 0; i < 1000; i++) {
		f = fopen(test_file_name, "w+");
		if (f) {
			fclose(f);
			unlink(test_file_name);
		}
	}
}