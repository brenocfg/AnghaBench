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
struct record {size_t bytes_written; TYPE_1__* session; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ perf_data__write (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ switch_output_size (struct record*) ; 
 int /*<<< orphan*/  switch_output_trigger ; 
 int /*<<< orphan*/  trigger_hit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int record__write(struct record *rec, void *bf, size_t size)
{
	if (perf_data__write(rec->session->data, bf, size) < 0) {
		pr_err("failed to write perf data, error: %m\n");
		return -1;
	}

	rec->bytes_written += size;

	if (switch_output_size(rec))
		trigger_hit(&switch_output_trigger);

	return 0;
}