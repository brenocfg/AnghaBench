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
struct perf_hpp_fmt {void* sort; void* color; void* collapse; void* cmp; int /*<<< orphan*/  entry; int /*<<< orphan*/  width; int /*<<< orphan*/  header; } ;
struct diff_hpp_fmt {int idx; struct perf_hpp_fmt fmt; } ;
struct data__file {struct diff_hpp_fmt* fmt; } ;

/* Variables and functions */
#define  PERF_HPP_DIFF__BASELINE 133 
#define  PERF_HPP_DIFF__CYCLES 132 
#define  PERF_HPP_DIFF__DELTA 131 
#define  PERF_HPP_DIFF__DELTA_ABS 130 
#define  PERF_HPP_DIFF__RATIO 129 
#define  PERF_HPP_DIFF__WEIGHTED_DIFF 128 
 void* hist_entry__cmp_baseline ; 
 void* hist_entry__cmp_delta ; 
 void* hist_entry__cmp_delta_abs ; 
 void* hist_entry__cmp_nop ; 
 void* hist_entry__cmp_ratio ; 
 void* hist_entry__cmp_wdiff ; 
 void* hpp__color_baseline ; 
 void* hpp__color_cycles ; 
 void* hpp__color_delta ; 
 void* hpp__color_ratio ; 
 void* hpp__color_wdiff ; 
 int /*<<< orphan*/  hpp__entry_global ; 
 int /*<<< orphan*/  hpp__header ; 
 int /*<<< orphan*/  hpp__width ; 
 int /*<<< orphan*/  init_header (struct data__file*,struct diff_hpp_fmt*) ; 
 int /*<<< orphan*/  perf_hpp__column_register (struct perf_hpp_fmt*) ; 
 int /*<<< orphan*/  perf_hpp__register_sort_field (struct perf_hpp_fmt*) ; 

__attribute__((used)) static void data__hpp_register(struct data__file *d, int idx)
{
	struct diff_hpp_fmt *dfmt = &d->fmt[idx];
	struct perf_hpp_fmt *fmt = &dfmt->fmt;

	dfmt->idx = idx;

	fmt->header = hpp__header;
	fmt->width  = hpp__width;
	fmt->entry  = hpp__entry_global;
	fmt->cmp    = hist_entry__cmp_nop;
	fmt->collapse = hist_entry__cmp_nop;

	/* TODO more colors */
	switch (idx) {
	case PERF_HPP_DIFF__BASELINE:
		fmt->color = hpp__color_baseline;
		fmt->sort  = hist_entry__cmp_baseline;
		break;
	case PERF_HPP_DIFF__DELTA:
		fmt->color = hpp__color_delta;
		fmt->sort  = hist_entry__cmp_delta;
		break;
	case PERF_HPP_DIFF__RATIO:
		fmt->color = hpp__color_ratio;
		fmt->sort  = hist_entry__cmp_ratio;
		break;
	case PERF_HPP_DIFF__WEIGHTED_DIFF:
		fmt->color = hpp__color_wdiff;
		fmt->sort  = hist_entry__cmp_wdiff;
		break;
	case PERF_HPP_DIFF__DELTA_ABS:
		fmt->color = hpp__color_delta;
		fmt->sort  = hist_entry__cmp_delta_abs;
		break;
	case PERF_HPP_DIFF__CYCLES:
		fmt->color = hpp__color_cycles;
		fmt->sort  = hist_entry__cmp_nop;
		break;
	default:
		fmt->sort  = hist_entry__cmp_nop;
		break;
	}

	init_header(d, dfmt);
	perf_hpp__column_register(fmt);
	perf_hpp__register_sort_field(fmt);
}