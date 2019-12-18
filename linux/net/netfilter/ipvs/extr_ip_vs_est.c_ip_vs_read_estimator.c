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
struct ip_vs_estimator {int cps; int inpps; int outpps; int inbps; int outbps; } ;
struct ip_vs_stats {struct ip_vs_estimator est; } ;
struct ip_vs_kstats {int cps; int inpps; int outpps; int inbps; int outbps; } ;

/* Variables and functions */

void ip_vs_read_estimator(struct ip_vs_kstats *dst, struct ip_vs_stats *stats)
{
	struct ip_vs_estimator *e = &stats->est;

	dst->cps = (e->cps + 0x1FF) >> 10;
	dst->inpps = (e->inpps + 0x1FF) >> 10;
	dst->outpps = (e->outpps + 0x1FF) >> 10;
	dst->inbps = (e->inbps + 0xF) >> 5;
	dst->outbps = (e->outbps + 0xF) >> 5;
}