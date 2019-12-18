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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dedup_tests ; 
 int /*<<< orphan*/  file_tests ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_info_tests ; 
 int /*<<< orphan*/  info_raw_tests ; 
 int /*<<< orphan*/  raw_tests ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *cmd)
{
	fprintf(stderr, "Usage: %s [-l] [[-r btf_raw_test_num (1 - %zu)] |\n"
			"\t[-g btf_get_info_test_num (1 - %zu)] |\n"
			"\t[-f btf_file_test_num (1 - %zu)] |\n"
			"\t[-k btf_prog_info_raw_test_num (1 - %zu)] |\n"
			"\t[-p (pretty print test)] |\n"
			"\t[-d btf_dedup_test_num (1 - %zu)]]\n",
		cmd, ARRAY_SIZE(raw_tests), ARRAY_SIZE(get_info_tests),
		ARRAY_SIZE(file_tests), ARRAY_SIZE(info_raw_tests),
		ARRAY_SIZE(dedup_tests));
}