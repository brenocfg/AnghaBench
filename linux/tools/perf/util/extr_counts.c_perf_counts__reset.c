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
struct perf_counts {int /*<<< orphan*/  values; int /*<<< orphan*/  loaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  xyarray__reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_counts__reset(struct perf_counts *counts)
{
	xyarray__reset(counts->loaded);
	xyarray__reset(counts->values);
}