#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 unsigned long avg_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rel_stddev_stats (double,unsigned long) ; 
 TYPE_1__ runtime ; 
 int /*<<< orphan*/  silent ; 
 double stddev_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throughput_stats ; 

__attribute__((used)) static void print_summary(void)
{
	unsigned long avg = avg_stats(&throughput_stats);
	double stddev = stddev_stats(&throughput_stats);

	printf("%sAveraged %ld operations/sec (+- %.2f%%), total secs = %d\n",
	       !silent ? "\n" : "", avg, rel_stddev_stats(stddev, avg),
	       (int) runtime.tv_sec);
}