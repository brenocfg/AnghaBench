#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {int tv_sec; int tv_usec; } ;
struct TYPE_3__ {int tv_sec; int tv_usec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NSEC_PER_SEC ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  RUSAGE_SELF ; 
 int getrusage (int /*<<< orphan*/ ,struct rusage*) ; 

__attribute__((used)) static u64 get_cpu_usage_nsec_parent(void)
{
	struct rusage ru;
	u64 sum;
	int err;

	err = getrusage(RUSAGE_SELF, &ru);
	BUG_ON(err);

	sum =  ru.ru_utime.tv_sec * NSEC_PER_SEC + ru.ru_utime.tv_usec * NSEC_PER_USEC;
	sum += ru.ru_stime.tv_sec * NSEC_PER_SEC + ru.ru_stime.tv_usec * NSEC_PER_USEC;

	return sum;
}