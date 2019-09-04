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
struct seq_file {int dummy; } ;
struct TYPE_4__ {scalar_t__* stats; } ;
struct TYPE_3__ {scalar_t__ ln_number; int /*<<< orphan*/  ln_type; } ;
struct gfs2_glock {TYPE_2__ gl_stats; TYPE_1__ gl_name; } ;

/* Variables and functions */
 size_t GFS2_LKS_DCOUNT ; 
 size_t GFS2_LKS_QCOUNT ; 
 size_t GFS2_LKS_SIRT ; 
 size_t GFS2_LKS_SIRTVAR ; 
 size_t GFS2_LKS_SRTT ; 
 size_t GFS2_LKS_SRTTB ; 
 size_t GFS2_LKS_SRTTVAR ; 
 size_t GFS2_LKS_SRTTVARB ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long,unsigned long long) ; 

__attribute__((used)) static int gfs2_glstats_seq_show(struct seq_file *seq, void *iter_ptr)
{
	struct gfs2_glock *gl = iter_ptr;

	seq_printf(seq, "G: n:%u/%llx rtt:%llu/%llu rttb:%llu/%llu irt:%llu/%llu dcnt: %llu qcnt: %llu\n",
		   gl->gl_name.ln_type,
		   (unsigned long long)gl->gl_name.ln_number,
		   (unsigned long long)gl->gl_stats.stats[GFS2_LKS_SRTT],
		   (unsigned long long)gl->gl_stats.stats[GFS2_LKS_SRTTVAR],
		   (unsigned long long)gl->gl_stats.stats[GFS2_LKS_SRTTB],
		   (unsigned long long)gl->gl_stats.stats[GFS2_LKS_SRTTVARB],
		   (unsigned long long)gl->gl_stats.stats[GFS2_LKS_SIRT],
		   (unsigned long long)gl->gl_stats.stats[GFS2_LKS_SIRTVAR],
		   (unsigned long long)gl->gl_stats.stats[GFS2_LKS_DCOUNT],
		   (unsigned long long)gl->gl_stats.stats[GFS2_LKS_QCOUNT]);
	return 0;
}