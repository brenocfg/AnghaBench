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
typedef  enum nfs_stat_bytecounters { ____Placeholder_nfs_stat_bytecounters } nfs_stat_bytecounters ;
struct TYPE_2__ {int /*<<< orphan*/ * bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  this_cpu_add (int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static inline void nfs_add_server_stats(const struct nfs_server *server,
					enum nfs_stat_bytecounters stat,
					long addend)
{
	this_cpu_add(server->io_stats->bytes[stat], addend);
}