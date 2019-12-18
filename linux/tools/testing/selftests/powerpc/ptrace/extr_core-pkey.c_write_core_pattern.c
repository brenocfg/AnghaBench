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
 int /*<<< orphan*/  SKIP_IF_MSG (int,char*) ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  core_pattern_file ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 size_t fwrite (char const*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int write_core_pattern(const char *core_pattern)
{
	size_t len = strlen(core_pattern), ret;
	FILE *f;

	f = fopen(core_pattern_file, "w");
	SKIP_IF_MSG(!f, "Try with root privileges");

	ret = fwrite(core_pattern, 1, len, f);
	fclose(f);
	if (ret != len) {
		perror("Error writing to core_pattern file");
		return TEST_FAIL;
	}

	return TEST_PASS;
}