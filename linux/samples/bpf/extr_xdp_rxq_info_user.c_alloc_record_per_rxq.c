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
struct record {int dummy; } ;
struct TYPE_2__ {unsigned int max_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAIL_MEM ; 
 TYPE_1__* bpf_map__def (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct record* malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct record*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  rx_queue_index_map ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct record *alloc_record_per_rxq(void)
{
	unsigned int nr_rxqs = bpf_map__def(rx_queue_index_map)->max_entries;
	struct record *array;
	size_t size;

	size = sizeof(struct record) * nr_rxqs;
	array = malloc(size);
	memset(array, 0, size);
	if (!array) {
		fprintf(stderr, "Mem alloc error (nr_rxqs:%u)\n", nr_rxqs);
		exit(EXIT_FAIL_MEM);
	}
	return array;
}