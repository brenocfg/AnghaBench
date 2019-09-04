#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lossless_map; int /*<<< orphan*/  ordered_map; int /*<<< orphan*/  map_name; int /*<<< orphan*/  map_type; int /*<<< orphan*/  descr; } ;
struct TYPE_4__ {int /*<<< orphan*/  lossless_map; int /*<<< orphan*/  ordered_map; int /*<<< orphan*/  map_name; int /*<<< orphan*/  map_type; int /*<<< orphan*/  descr; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int count_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_test_pprint () ; 
 TYPE_2__ pprint_test_template ; 
 TYPE_1__* pprint_tests_meta ; 

__attribute__((used)) static int test_pprint(void)
{
	unsigned int i;
	int err = 0;

	for (i = 0; i < ARRAY_SIZE(pprint_tests_meta); i++) {
		pprint_test_template.descr = pprint_tests_meta[i].descr;
		pprint_test_template.map_type = pprint_tests_meta[i].map_type;
		pprint_test_template.map_name = pprint_tests_meta[i].map_name;
		pprint_test_template.ordered_map = pprint_tests_meta[i].ordered_map;
		pprint_test_template.lossless_map = pprint_tests_meta[i].lossless_map;

		err |= count_result(do_test_pprint());
	}

	return err;
}