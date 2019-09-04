#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  double u64 ;
struct sym_hist {int nr_samples; int period; TYPE_1__* addr; } ;
struct TYPE_6__ {int nr_non_filtered_samples; int total_period; } ;
struct hists {TYPE_3__ stats; } ;
struct TYPE_5__ {double period; unsigned int nr_samples; } ;
struct annotation_data {double* percent; TYPE_2__ he; } ;
typedef  size_t s64 ;
struct TYPE_4__ {scalar_t__ period; scalar_t__ nr_samples; } ;

/* Variables and functions */
 size_t PERCENT_HITS_GLOBAL ; 
 size_t PERCENT_HITS_LOCAL ; 
 size_t PERCENT_PERIOD_GLOBAL ; 
 size_t PERCENT_PERIOD_LOCAL ; 

__attribute__((used)) static void calc_percent(struct sym_hist *sym_hist,
			 struct hists *hists,
			 struct annotation_data *data,
			 s64 offset, s64 end)
{
	unsigned int hits = 0;
	u64 period = 0;

	while (offset < end) {
		hits   += sym_hist->addr[offset].nr_samples;
		period += sym_hist->addr[offset].period;
		++offset;
	}

	if (sym_hist->nr_samples) {
		data->he.period     = period;
		data->he.nr_samples = hits;
		data->percent[PERCENT_HITS_LOCAL] = 100.0 * hits / sym_hist->nr_samples;
	}

	if (hists->stats.nr_non_filtered_samples)
		data->percent[PERCENT_HITS_GLOBAL] = 100.0 * hits / hists->stats.nr_non_filtered_samples;

	if (sym_hist->period)
		data->percent[PERCENT_PERIOD_LOCAL] = 100.0 * period / sym_hist->period;

	if (hists->stats.total_period)
		data->percent[PERCENT_PERIOD_GLOBAL] = 100.0 * period / hists->stats.total_period;
}