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
struct btf_dump {int decl_stack_cnt; int decl_stack_cap; int /*<<< orphan*/ * decl_stack; } ;
typedef  int /*<<< orphan*/  new_stack ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 size_t max (int,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int btf_dump_push_decl_stack_id(struct btf_dump *d, __u32 id)
{
	__u32 *new_stack;
	size_t new_cap;

	if (d->decl_stack_cnt >= d->decl_stack_cap) {
		new_cap = max(16, d->decl_stack_cap * 3 / 2);
		new_stack = realloc(d->decl_stack,
				    new_cap * sizeof(new_stack[0]));
		if (!new_stack)
			return -ENOMEM;
		d->decl_stack = new_stack;
		d->decl_stack_cap = new_cap;
	}

	d->decl_stack[d->decl_stack_cnt++] = id;

	return 0;
}