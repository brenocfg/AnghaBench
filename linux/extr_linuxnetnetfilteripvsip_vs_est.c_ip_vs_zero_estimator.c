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
struct ip_vs_kstats {int /*<<< orphan*/  outpkts; int /*<<< orphan*/  inpkts; int /*<<< orphan*/  conns; int /*<<< orphan*/  outbytes; int /*<<< orphan*/  inbytes; } ;
struct ip_vs_estimator {scalar_t__ outbps; scalar_t__ inbps; scalar_t__ outpps; scalar_t__ inpps; scalar_t__ cps; int /*<<< orphan*/  last_outpkts; int /*<<< orphan*/  last_inpkts; int /*<<< orphan*/  last_conns; int /*<<< orphan*/  last_outbytes; int /*<<< orphan*/  last_inbytes; } ;
struct ip_vs_stats {struct ip_vs_kstats kstats; struct ip_vs_estimator est; } ;

/* Variables and functions */

void ip_vs_zero_estimator(struct ip_vs_stats *stats)
{
	struct ip_vs_estimator *est = &stats->est;
	struct ip_vs_kstats *k = &stats->kstats;

	/* reset counters, caller must hold the stats->lock lock */
	est->last_inbytes = k->inbytes;
	est->last_outbytes = k->outbytes;
	est->last_conns = k->conns;
	est->last_inpkts = k->inpkts;
	est->last_outpkts = k->outpkts;
	est->cps = 0;
	est->inpps = 0;
	est->outpps = 0;
	est->inbps = 0;
	est->outbps = 0;
}