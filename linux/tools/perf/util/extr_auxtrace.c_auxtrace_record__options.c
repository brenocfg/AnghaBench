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
struct record_opts {int dummy; } ;
struct evlist {int dummy; } ;
struct auxtrace_record {int (* recording_options ) (struct auxtrace_record*,struct evlist*,struct record_opts*) ;} ;

/* Variables and functions */
 int stub1 (struct auxtrace_record*,struct evlist*,struct record_opts*) ; 

int auxtrace_record__options(struct auxtrace_record *itr,
			     struct evlist *evlist,
			     struct record_opts *opts)
{
	if (itr)
		return itr->recording_options(itr, evlist, opts);
	return 0;
}