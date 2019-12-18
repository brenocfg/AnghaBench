#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  percpu_map; int /*<<< orphan*/  lossless_map; int /*<<< orphan*/  ordered_map; int /*<<< orphan*/  map_name; int /*<<< orphan*/  map_type; int /*<<< orphan*/  descr; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int count_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_test_pprint (unsigned int) ; 
 TYPE_1__* pprint_test_template ; 
 TYPE_1__* pprint_tests_meta ; 

__attribute__((used)) static int test_pprint(void)
{
	unsigned int i;
	int err = 0;

	/* test various maps with the first test template */
	for (i = 0; i < ARRAY_SIZE(pprint_tests_meta); i++) {
		pprint_test_template[0].descr = pprint_tests_meta[i].descr;
		pprint_test_template[0].map_type = pprint_tests_meta[i].map_type;
		pprint_test_template[0].map_name = pprint_tests_meta[i].map_name;
		pprint_test_template[0].ordered_map = pprint_tests_meta[i].ordered_map;
		pprint_test_template[0].lossless_map = pprint_tests_meta[i].lossless_map;
		pprint_test_template[0].percpu_map = pprint_tests_meta[i].percpu_map;

		err |= count_result(do_test_pprint(0));
	}

	/* test rest test templates with the first map */
	for (i = 1; i < ARRAY_SIZE(pprint_test_template); i++) {
		pprint_test_template[i].descr = pprint_tests_meta[0].descr;
		pprint_test_template[i].map_type = pprint_tests_meta[0].map_type;
		pprint_test_template[i].map_name = pprint_tests_meta[0].map_name;
		pprint_test_template[i].ordered_map = pprint_tests_meta[0].ordered_map;
		pprint_test_template[i].lossless_map = pprint_tests_meta[0].lossless_map;
		pprint_test_template[i].percpu_map = pprint_tests_meta[0].percpu_map;
		err |= count_result(do_test_pprint(i));
	}

	return err;
}