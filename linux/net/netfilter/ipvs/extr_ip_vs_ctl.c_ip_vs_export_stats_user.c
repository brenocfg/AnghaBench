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
typedef  void* u32 ;
struct ip_vs_stats_user {void* outbps; void* inbps; void* outpps; void* inpps; void* cps; int /*<<< orphan*/  outbytes; int /*<<< orphan*/  inbytes; void* outpkts; void* inpkts; void* conns; } ;
struct ip_vs_kstats {scalar_t__ outbps; scalar_t__ inbps; scalar_t__ outpps; scalar_t__ inpps; scalar_t__ cps; int /*<<< orphan*/  outbytes; int /*<<< orphan*/  inbytes; scalar_t__ outpkts; scalar_t__ inpkts; scalar_t__ conns; } ;

/* Variables and functions */

__attribute__((used)) static void
ip_vs_export_stats_user(struct ip_vs_stats_user *dst, struct ip_vs_kstats *src)
{
	dst->conns = (u32)src->conns;
	dst->inpkts = (u32)src->inpkts;
	dst->outpkts = (u32)src->outpkts;
	dst->inbytes = src->inbytes;
	dst->outbytes = src->outbytes;
	dst->cps = (u32)src->cps;
	dst->inpps = (u32)src->inpps;
	dst->outpps = (u32)src->outpps;
	dst->inbps = (u32)src->inbps;
	dst->outbps = (u32)src->outbps;
}