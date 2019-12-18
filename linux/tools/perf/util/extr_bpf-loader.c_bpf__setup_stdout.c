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
struct evsel {int dummy; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct evsel*) ; 
 struct evsel* bpf__setup_output_event (struct evlist*,char*) ; 

int bpf__setup_stdout(struct evlist *evlist)
{
	struct evsel *evsel = bpf__setup_output_event(evlist, "__bpf_stdout__");
	return PTR_ERR_OR_ZERO(evsel);
}