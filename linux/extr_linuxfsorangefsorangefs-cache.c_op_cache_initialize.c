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
struct orangefs_kernel_op_s {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ORANGEFS_CACHE_CREATE_FLAGS ; 
 int /*<<< orphan*/  gossip_err (char*) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int next_tag_value ; 
 int /*<<< orphan*/  next_tag_value_lock ; 
 int /*<<< orphan*/  op_cache ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int op_cache_initialize(void)
{
	op_cache = kmem_cache_create("orangefs_op_cache",
				     sizeof(struct orangefs_kernel_op_s),
				     0,
				     ORANGEFS_CACHE_CREATE_FLAGS,
				     NULL);

	if (!op_cache) {
		gossip_err("Cannot create orangefs_op_cache\n");
		return -ENOMEM;
	}

	/* initialize our atomic tag counter */
	spin_lock(&next_tag_value_lock);
	next_tag_value = 100;
	spin_unlock(&next_tag_value_lock);
	return 0;
}