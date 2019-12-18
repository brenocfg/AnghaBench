#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int count; } ;
struct TYPE_10__ {TYPE_1__ step; } ;
struct TYPE_11__ {TYPE_2__ run; } ;
struct TYPE_12__ {TYPE_3__ pkt; } ;
struct TYPE_13__ {TYPE_4__ tran; } ;
typedef  TYPE_5__ libqnxr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSMSG_RUN ; 
 int /*<<< orphan*/  DSMSG_RUN_COUNT ; 
 int /*<<< orphan*/  DStMsg_run ; 
 int /*<<< orphan*/  SET_CHANNEL_DEBUG ; 
 int /*<<< orphan*/  nto_send (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  nto_send_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qnxr_send_vcont (libqnxr_t *g, int step, int thread_id) {
	if (!g) return -1;

	nto_send_init (g, DStMsg_run, step ? DSMSG_RUN_COUNT : DSMSG_RUN,
		       SET_CHANNEL_DEBUG);
	g->tran.pkt.run.step.count = 1;
	nto_send (g, sizeof (g->tran.pkt.run), 1);
	return 0;
}