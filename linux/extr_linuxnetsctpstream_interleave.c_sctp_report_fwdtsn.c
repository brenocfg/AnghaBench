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
struct sctp_ulpq {TYPE_2__* asoc; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_3__ {int /*<<< orphan*/  tsn_map; } ;
struct TYPE_4__ {TYPE_1__ peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  sctp_tsnmap_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpq_abort_pd (struct sctp_ulpq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpq_reasm_flushtsn (struct sctp_ulpq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_report_fwdtsn(struct sctp_ulpq *ulpq, __u32 ftsn)
{
	/* Move the Cumulattive TSN Ack ahead. */
	sctp_tsnmap_skip(&ulpq->asoc->peer.tsn_map, ftsn);
	/* purge the fragmentation queue */
	sctp_ulpq_reasm_flushtsn(ulpq, ftsn);
	/* Abort any in progress partial delivery. */
	sctp_ulpq_abort_pd(ulpq, GFP_ATOMIC);
}