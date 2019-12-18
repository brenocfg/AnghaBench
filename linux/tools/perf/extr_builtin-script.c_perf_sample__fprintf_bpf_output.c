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
struct printer_data {int member_1; int member_2; scalar_t__ hit_nul; scalar_t__ is_printable; int /*<<< orphan*/  member_0; } ;
struct perf_sample {unsigned int raw_size; scalar_t__ raw_data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int binary__fprintf (scalar_t__,unsigned int,int,int /*<<< orphan*/ ,struct printer_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  sample__fprintf_bpf_output ; 

__attribute__((used)) static int perf_sample__fprintf_bpf_output(struct perf_sample *sample, FILE *fp)
{
	unsigned int nr_bytes = sample->raw_size;
	struct printer_data printer_data = {0, false, true};
	int printed = binary__fprintf(sample->raw_data, nr_bytes, 8,
				      sample__fprintf_bpf_output, &printer_data, fp);

	if (printer_data.is_printable && printer_data.hit_nul)
		printed += fprintf(fp, "%17s \"%s\"\n", "BPF string:", (char *)(sample->raw_data));

	return printed;
}