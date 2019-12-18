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
struct perf_cpu_map {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  cpu_map__snprint (struct perf_cpu_map*,char*,int) ; 
 size_t fprintf (int /*<<< orphan*/ *,char*,char*) ; 

size_t cpu_map__fprintf(struct perf_cpu_map *map, FILE *fp)
{
#define BUFSIZE 1024
	char buf[BUFSIZE];

	cpu_map__snprint(map, buf, sizeof(buf));
	return fprintf(fp, "%s\n", buf);
#undef BUFSIZE
}