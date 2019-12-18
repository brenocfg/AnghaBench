#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct res_sample {int /*<<< orphan*/  tid; int /*<<< orphan*/  cpu; int /*<<< orphan*/  time; } ;
struct perf_sample {int /*<<< orphan*/  tid; int /*<<< orphan*/  cpu; int /*<<< orphan*/  time; } ;
struct hist_entry {scalar_t__ num_res; struct res_sample* res_samples; } ;
struct TYPE_2__ {scalar_t__ res_sample; } ;

/* Variables and functions */
 int random_max (scalar_t__) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static void hists__res_sample(struct hist_entry *he, struct perf_sample *sample)
{
	struct res_sample *r;
	int j;

	if (he->num_res < symbol_conf.res_sample) {
		j = he->num_res++;
	} else {
		j = random_max(symbol_conf.res_sample);
	}
	r = &he->res_samples[j];
	r->time = sample->time;
	r->cpu = sample->cpu;
	r->tid = sample->tid;
}