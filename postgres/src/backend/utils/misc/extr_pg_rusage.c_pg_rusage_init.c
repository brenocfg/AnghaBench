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
struct TYPE_3__ {int /*<<< orphan*/  tv; int /*<<< orphan*/  ru; } ;
typedef  TYPE_1__ PGRUsage ;

/* Variables and functions */
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pg_rusage_init(PGRUsage *ru0)
{
	getrusage(RUSAGE_SELF, &ru0->ru);
	gettimeofday(&ru0->tv, NULL);
}