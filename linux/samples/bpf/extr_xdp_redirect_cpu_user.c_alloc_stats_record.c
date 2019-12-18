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
struct TYPE_8__ {void* cpu; } ;
struct TYPE_7__ {void* cpu; } ;
struct TYPE_6__ {void* cpu; } ;
struct TYPE_10__ {void* cpu; } ;
struct stats_record {TYPE_4__* enq; TYPE_3__ exception; TYPE_2__ kthread; TYPE_1__ redir_err; TYPE_5__ rx_cnt; } ;
struct TYPE_9__ {void* cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAIL_MEM ; 
 int MAX_CPUS ; 
 void* alloc_record_per_cpu () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct stats_record* malloc (int) ; 
 int /*<<< orphan*/  memset (struct stats_record*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct stats_record *alloc_stats_record(void)
{
	struct stats_record *rec;
	int i;

	rec = malloc(sizeof(*rec));
	memset(rec, 0, sizeof(*rec));
	if (!rec) {
		fprintf(stderr, "Mem alloc error\n");
		exit(EXIT_FAIL_MEM);
	}
	rec->rx_cnt.cpu    = alloc_record_per_cpu();
	rec->redir_err.cpu = alloc_record_per_cpu();
	rec->kthread.cpu   = alloc_record_per_cpu();
	rec->exception.cpu = alloc_record_per_cpu();
	for (i = 0; i < MAX_CPUS; i++)
		rec->enq[i].cpu = alloc_record_per_cpu();

	return rec;
}