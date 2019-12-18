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
struct record_opts {int /*<<< orphan*/  affinity; } ;
struct option {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_AFFINITY_CPU ; 
 int /*<<< orphan*/  PERF_AFFINITY_NODE ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int record__parse_affinity(const struct option *opt, const char *str, int unset)
{
	struct record_opts *opts = (struct record_opts *)opt->value;

	if (unset || !str)
		return 0;

	if (!strcasecmp(str, "node"))
		opts->affinity = PERF_AFFINITY_NODE;
	else if (!strcasecmp(str, "cpu"))
		opts->affinity = PERF_AFFINITY_CPU;

	return 0;
}