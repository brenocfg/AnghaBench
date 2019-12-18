#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double count; double sum; double sum2; } ;
typedef  TYPE_1__ SimpleStats ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,double) ; 
 double sqrt (double) ; 

__attribute__((used)) static void
printSimpleStats(const char *prefix, SimpleStats *ss)
{
	if (ss->count > 0)
	{
		double		latency = ss->sum / ss->count;
		double		stddev = sqrt(ss->sum2 / ss->count - latency * latency);

		printf("%s average = %.3f ms\n", prefix, 0.001 * latency);
		printf("%s stddev = %.3f ms\n", prefix, 0.001 * stddev);
	}
}