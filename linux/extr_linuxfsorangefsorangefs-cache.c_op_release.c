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
struct orangefs_kernel_op_s {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOSSIP_CACHE_DEBUG ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,struct orangefs_kernel_op_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gossip_err (char*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct orangefs_kernel_op_s*) ; 
 int /*<<< orphan*/  llu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_cache ; 

void op_release(struct orangefs_kernel_op_s *orangefs_op)
{
	if (orangefs_op) {
		gossip_debug(GOSSIP_CACHE_DEBUG,
			     "Releasing OP (%p: %llu)\n",
			     orangefs_op,
			     llu(orangefs_op->tag));
		kmem_cache_free(op_cache, orangefs_op);
	} else {
		gossip_err("NULL pointer in op_release\n");
	}
}