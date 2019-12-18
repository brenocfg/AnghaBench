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
struct evlist {int dummy; } ;
struct auxtrace_record {size_t (* info_priv_size ) (struct auxtrace_record*,struct evlist*) ;} ;

/* Variables and functions */
 size_t stub1 (struct auxtrace_record*,struct evlist*) ; 

size_t auxtrace_record__info_priv_size(struct auxtrace_record *itr,
				       struct evlist *evlist)
{
	if (itr)
		return itr->info_priv_size(itr, evlist);
	return 0;
}