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
struct perf_sample {int /*<<< orphan*/  user_regs; int /*<<< orphan*/  intr_regs; } ;
struct perf_event_attr {int /*<<< orphan*/  sample_regs_user; int /*<<< orphan*/  sample_regs_intr; } ;
struct TYPE_2__ {struct perf_event_attr attr; } ;
struct evsel {TYPE_1__ core; } ;
typedef  int /*<<< orphan*/  bf ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  _PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/  pydict_set_item_string_decref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regs_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void set_regs_in_dict(PyObject *dict,
			     struct perf_sample *sample,
			     struct evsel *evsel)
{
	struct perf_event_attr *attr = &evsel->core.attr;
	char bf[512];

	regs_map(&sample->intr_regs, attr->sample_regs_intr, bf, sizeof(bf));

	pydict_set_item_string_decref(dict, "iregs",
			_PyUnicode_FromString(bf));

	regs_map(&sample->user_regs, attr->sample_regs_user, bf, sizeof(bf));

	pydict_set_item_string_decref(dict, "uregs",
			_PyUnicode_FromString(bf));
}