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
struct seq_file {int dummy; } ;
struct bpf_map {TYPE_1__* ops; } ;
struct TYPE_4__ {void* key; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* map_seq_show_elem ) (struct bpf_map*,void*,struct seq_file*) ;} ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 TYPE_2__* map_iter (struct seq_file*) ; 
 struct bpf_map* seq_file_to_map (struct seq_file*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  stub1 (struct bpf_map*,void*,struct seq_file*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int map_seq_show(struct seq_file *m, void *v)
{
	struct bpf_map *map = seq_file_to_map(m);
	void *key = map_iter(m)->key;

	if (unlikely(v == SEQ_START_TOKEN)) {
		seq_puts(m, "# WARNING!! The output is for debug purpose only\n");
		seq_puts(m, "# WARNING!! The output format will change\n");
	} else {
		map->ops->map_seq_show_elem(map, key, m);
	}

	return 0;
}