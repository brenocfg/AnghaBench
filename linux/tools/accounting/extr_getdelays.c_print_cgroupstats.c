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
struct cgroupstats {scalar_t__ nr_uninterruptible; scalar_t__ nr_stopped; scalar_t__ nr_running; scalar_t__ nr_io_wait; scalar_t__ nr_sleeping; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long) ; 

__attribute__((used)) static void print_cgroupstats(struct cgroupstats *c)
{
	printf("sleeping %llu, blocked %llu, running %llu, stopped %llu, "
		"uninterruptible %llu\n", (unsigned long long)c->nr_sleeping,
		(unsigned long long)c->nr_io_wait,
		(unsigned long long)c->nr_running,
		(unsigned long long)c->nr_stopped,
		(unsigned long long)c->nr_uninterruptible);
}