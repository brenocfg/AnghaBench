#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct u64rec {scalar_t__ processed; } ;
struct TYPE_4__ {int /*<<< orphan*/  processed; } ;
struct record_u64 {TYPE_2__ total; TYPE_1__* cpu; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;
struct TYPE_3__ {scalar_t__ processed; } ;

/* Variables and functions */
 scalar_t__ bpf_map_lookup_elem (int,int*,struct u64rec*) ; 
 unsigned int bpf_num_possible_cpus () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gettime () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool map_collect_record_u64(int fd, __u32 key, struct record_u64 *rec)
{
	/* For percpu maps, userspace gets a value per possible CPU */
	unsigned int nr_cpus = bpf_num_possible_cpus();
	struct u64rec values[nr_cpus];
	__u64 sum_total = 0;
	int i;

	if ((bpf_map_lookup_elem(fd, &key, values)) != 0) {
		fprintf(stderr,
			"ERR: bpf_map_lookup_elem failed key:0x%X\n", key);
		return false;
	}
	/* Get time as close as possible to reading map contents */
	rec->timestamp = gettime();

	/* Record and sum values from each CPU */
	for (i = 0; i < nr_cpus; i++) {
		rec->cpu[i].processed = values[i].processed;
		sum_total            += values[i].processed;
	}
	rec->total.processed = sum_total;
	return true;
}