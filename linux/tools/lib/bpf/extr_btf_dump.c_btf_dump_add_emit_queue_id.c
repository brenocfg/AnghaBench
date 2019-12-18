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
struct btf_dump {int emit_queue_cnt; int emit_queue_cap; int /*<<< orphan*/ * emit_queue; } ;
typedef  int /*<<< orphan*/  new_queue ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 size_t max (int,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int btf_dump_add_emit_queue_id(struct btf_dump *d, __u32 id)
{
	__u32 *new_queue;
	size_t new_cap;

	if (d->emit_queue_cnt >= d->emit_queue_cap) {
		new_cap = max(16, d->emit_queue_cap * 3 / 2);
		new_queue = realloc(d->emit_queue,
				    new_cap * sizeof(new_queue[0]));
		if (!new_queue)
			return -ENOMEM;
		d->emit_queue = new_queue;
		d->emit_queue_cap = new_cap;
	}

	d->emit_queue[d->emit_queue_cnt++] = id;
	return 0;
}