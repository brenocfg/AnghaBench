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
struct nfs_server {TYPE_1__* io_stats; } ;
typedef  enum nfs_stat_eventcounters { ____Placeholder_nfs_stat_eventcounters } nfs_stat_eventcounters ;
struct TYPE_2__ {int /*<<< orphan*/ * events; } ;

/* Variables and functions */
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nfs_inc_server_stats(const struct nfs_server *server,
					enum nfs_stat_eventcounters stat)
{
	this_cpu_inc(server->io_stats->events[stat]);
}