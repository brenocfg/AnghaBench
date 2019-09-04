#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct stats_record* cpu; } ;
struct TYPE_9__ {struct stats_record* cpu; } ;
struct TYPE_8__ {struct stats_record* cpu; } ;
struct TYPE_7__ {struct stats_record* cpu; } ;
struct stats_record {TYPE_5__ rx_cnt; TYPE_4__ redir_err; TYPE_3__ kthread; TYPE_2__ exception; TYPE_1__* enq; } ;
struct TYPE_6__ {struct stats_record* cpu; } ;

/* Variables and functions */
 int MAX_CPUS ; 
 int /*<<< orphan*/  free (struct stats_record*) ; 

__attribute__((used)) static void free_stats_record(struct stats_record *r)
{
	int i;

	for (i = 0; i < MAX_CPUS; i++)
		free(r->enq[i].cpu);
	free(r->exception.cpu);
	free(r->kthread.cpu);
	free(r->redir_err.cpu);
	free(r->rx_cnt.cpu);
	free(r);
}