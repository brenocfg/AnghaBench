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
struct runtime_stat {int dummy; } ;
struct perf_stat_config {int stats_num; int /*<<< orphan*/ * stats; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  runtime_stat__init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int runtime_stat_new(struct perf_stat_config *config, int nthreads)
{
	int i;

	config->stats = calloc(nthreads, sizeof(struct runtime_stat));
	if (!config->stats)
		return -1;

	config->stats_num = nthreads;

	for (i = 0; i < nthreads; i++)
		runtime_stat__init(&config->stats[i]);

	return 0;
}