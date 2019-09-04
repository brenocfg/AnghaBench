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
struct stats_record {int /*<<< orphan*/  exception; int /*<<< orphan*/  kthread; int /*<<< orphan*/ * enq; int /*<<< orphan*/  redir_err; int /*<<< orphan*/  rx_cnt; } ;

/* Variables and functions */
 int MAX_CPUS ; 
 int /*<<< orphan*/  map_collect_percpu (int,int,int /*<<< orphan*/ *) ; 
 int* map_fd ; 

__attribute__((used)) static void stats_collect(struct stats_record *rec)
{
	int fd, i;

	fd = map_fd[1]; /* map: rx_cnt */
	map_collect_percpu(fd, 0, &rec->rx_cnt);

	fd = map_fd[2]; /* map: redirect_err_cnt */
	map_collect_percpu(fd, 1, &rec->redir_err);

	fd = map_fd[3]; /* map: cpumap_enqueue_cnt */
	for (i = 0; i < MAX_CPUS; i++)
		map_collect_percpu(fd, i, &rec->enq[i]);

	fd = map_fd[4]; /* map: cpumap_kthread_cnt */
	map_collect_percpu(fd, 0, &rec->kthread);

	fd = map_fd[8]; /* map: exception_cnt */
	map_collect_percpu(fd, 0, &rec->exception);
}