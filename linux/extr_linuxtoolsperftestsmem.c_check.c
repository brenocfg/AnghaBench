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
typedef  union perf_mem_data_src {int dummy; } perf_mem_data_src ;
struct mem_info {union perf_mem_data_src data_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 scalar_t__ perf_mem__lvl_scnprintf (char*,int,struct mem_info*) ; 
 int perf_mem__snp_scnprintf (char*,int,struct mem_info*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int check(union perf_mem_data_src data_src,
		  const char *string)
{
	char out[100];
	char failure[100];
	struct mem_info mi = { .data_src = data_src };

	int n;

	n = perf_mem__snp_scnprintf(out, sizeof out, &mi);
	n += perf_mem__lvl_scnprintf(out + n, sizeof out - n, &mi);
	scnprintf(failure, sizeof failure, "unexpected %s", out);
	TEST_ASSERT_VAL(failure, !strcmp(string, out));
	return 0;
}