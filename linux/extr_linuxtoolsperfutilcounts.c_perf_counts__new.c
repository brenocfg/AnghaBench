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
struct xyarray {int dummy; } ;
struct perf_counts_values {int dummy; } ;
struct perf_counts {struct xyarray* values; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct perf_counts*) ; 
 struct xyarray* xyarray__new (int,int,int) ; 
 struct perf_counts* zalloc (int) ; 

struct perf_counts *perf_counts__new(int ncpus, int nthreads)
{
	struct perf_counts *counts = zalloc(sizeof(*counts));

	if (counts) {
		struct xyarray *values;

		values = xyarray__new(ncpus, nthreads, sizeof(struct perf_counts_values));
		if (!values) {
			free(counts);
			return NULL;
		}

		counts->values = values;
	}

	return counts;
}