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
struct TYPE_5__ {unsigned int nr_ranges; TYPE_1__* ranges; } ;
struct TYPE_6__ {TYPE_2__ array; } ;
struct bpf_map_op {TYPE_3__ k; } ;
struct bpf_map_def {int dummy; } ;
typedef  int (* map_config_func_t ) (char const*,int,struct bpf_map_def const*,struct bpf_map_op*,unsigned int*,void*) ;
struct TYPE_4__ {unsigned int start; size_t length; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,char const*,unsigned int) ; 

__attribute__((used)) static int
foreach_key_array_ranges(map_config_func_t func, void *arg,
			 const char *name, int map_fd,
			 const struct bpf_map_def *pdef,
			 struct bpf_map_op *op)
{
	unsigned int i, j;
	int err;

	for (i = 0; i < op->k.array.nr_ranges; i++) {
		unsigned int start = op->k.array.ranges[i].start;
		size_t length = op->k.array.ranges[i].length;

		for (j = 0; j < length; j++) {
			unsigned int idx = start + j;

			err = func(name, map_fd, pdef, op, &idx, arg);
			if (err) {
				pr_debug("ERROR: failed to insert value to %s[%u]\n",
					 name, idx);
				return err;
			}
		}
	}
	return 0;
}