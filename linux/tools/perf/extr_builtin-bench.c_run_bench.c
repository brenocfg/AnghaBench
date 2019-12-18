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
typedef  int (* bench_fn_t ) (int,char const**) ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PR_SET_NAME ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*,char const*) ; 
 int strlen (char const*) ; 
 char* zalloc (int) ; 

__attribute__((used)) static int run_bench(const char *coll_name, const char *bench_name, bench_fn_t fn,
		     int argc, const char **argv)
{
	int size;
	char *name;
	int ret;

	size = strlen(coll_name) + 1 + strlen(bench_name) + 1;

	name = zalloc(size);
	BUG_ON(!name);

	scnprintf(name, size, "%s-%s", coll_name, bench_name);

	prctl(PR_SET_NAME, name);
	argv[0] = name;

	ret = fn(argc, argv);

	free(name);

	return ret;
}