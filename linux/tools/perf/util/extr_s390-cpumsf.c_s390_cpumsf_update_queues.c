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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int new_data; } ;
struct s390_cpumsf {TYPE_1__ queues; } ;

/* Variables and functions */
 int s390_cpumsf_setup_queues (struct s390_cpumsf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s390_cpumsf_update_queues(struct s390_cpumsf *sf, u64 ts)
{
	if (!sf->queues.new_data)
		return 0;

	sf->queues.new_data = false;
	return s390_cpumsf_setup_queues(sf, ts);
}