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
struct perf_session {int dummy; } ;
struct perf_record_auxtrace_info {int dummy; } ;
struct auxtrace_record {int (* info_fill ) (struct auxtrace_record*,struct perf_session*,struct perf_record_auxtrace_info*,size_t) ;} ;

/* Variables and functions */
 int auxtrace_not_supported () ; 
 int stub1 (struct auxtrace_record*,struct perf_session*,struct perf_record_auxtrace_info*,size_t) ; 

int auxtrace_record__info_fill(struct auxtrace_record *itr,
			       struct perf_session *session,
			       struct perf_record_auxtrace_info *auxtrace_info,
			       size_t priv_size)
{
	if (itr)
		return itr->info_fill(itr, session, auxtrace_info, priv_size);
	return auxtrace_not_supported();
}