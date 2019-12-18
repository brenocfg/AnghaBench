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
struct perf_sample {int /*<<< orphan*/  data_src; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct mem_info {TYPE_1__ data_src; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyLong_FromUnsignedLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/  perf_script__meminfo_scnprintf (char*,int,struct mem_info*) ; 
 int /*<<< orphan*/  pydict_set_item_string_decref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_sample_datasrc_in_dict(PyObject *dict,
				       struct perf_sample *sample)
{
	struct mem_info mi = { .data_src.val = sample->data_src };
	char decode[100];

	pydict_set_item_string_decref(dict, "datasrc",
			PyLong_FromUnsignedLongLong(sample->data_src));

	perf_script__meminfo_scnprintf(decode, 100, &mi);

	pydict_set_item_string_decref(dict, "datasrc_decode",
			_PyUnicode_FromString(decode));
}