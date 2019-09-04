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
struct u64rec {int dummy; } ;
struct TYPE_9__ {void* cpu; } ;
struct TYPE_8__ {void* cpu; } ;
struct stats_record {TYPE_5__* xdp_cpumap_enqueue; TYPE_4__ xdp_devmap_xmit; TYPE_3__ xdp_cpumap_kthread; TYPE_2__* xdp_exception; TYPE_1__* xdp_redirect; } ;
struct datarec {int dummy; } ;
struct TYPE_10__ {void* cpu; } ;
struct TYPE_7__ {void* cpu; } ;
struct TYPE_6__ {void* cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAIL_MEM ; 
 int MAX_CPUS ; 
 int REDIR_RES_MAX ; 
 int XDP_ACTION_MAX ; 
 void* alloc_rec_per_cpu (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct stats_record* malloc (int) ; 
 int /*<<< orphan*/  memset (struct stats_record*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct stats_record *alloc_stats_record(void)
{
	struct stats_record *rec;
	int rec_sz;
	int i;

	/* Alloc main stats_record structure */
	rec = malloc(sizeof(*rec));
	memset(rec, 0, sizeof(*rec));
	if (!rec) {
		fprintf(stderr, "Mem alloc error\n");
		exit(EXIT_FAIL_MEM);
	}

	/* Alloc stats stored per CPU for each record */
	rec_sz = sizeof(struct u64rec);
	for (i = 0; i < REDIR_RES_MAX; i++)
		rec->xdp_redirect[i].cpu = alloc_rec_per_cpu(rec_sz);

	for (i = 0; i < XDP_ACTION_MAX; i++)
		rec->xdp_exception[i].cpu = alloc_rec_per_cpu(rec_sz);

	rec_sz = sizeof(struct datarec);
	rec->xdp_cpumap_kthread.cpu = alloc_rec_per_cpu(rec_sz);
	rec->xdp_devmap_xmit.cpu    = alloc_rec_per_cpu(rec_sz);

	for (i = 0; i < MAX_CPUS; i++)
		rec->xdp_cpumap_enqueue[i].cpu = alloc_rec_per_cpu(rec_sz);

	return rec;
}